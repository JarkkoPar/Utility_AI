#include "agent.h"
#include "sensors.h"
#include "behaviour.h"
#include "behaviour_group.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>


using namespace godot;

// Method binds.

void UtilityAIAgent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_current_behaviour_node"), &UtilityAIAgent::set_current_behaviour_node);
    ClassDB::bind_method(D_METHOD("get_current_behaviour_node"), &UtilityAIAgent::get_current_behaviour_node);

    ClassDB::bind_method(D_METHOD("set_current_action_node"), &UtilityAIAgent::set_current_action_node);
    ClassDB::bind_method(D_METHOD("get_current_action_node"), &UtilityAIAgent::get_current_action_node);


    ClassDB::bind_method(D_METHOD("evaluate_options", "delta"), &UtilityAIAgent::evaluate_options);
    ClassDB::bind_method(D_METHOD("update_current_behaviour"), &UtilityAIAgent::update_current_behaviour);
    ClassDB::bind_method(D_METHOD("abort_current_behaviour"), &UtilityAIAgent::abort_current_behaviour);

    ClassDB::bind_method(D_METHOD("set_num_behaviours_to_select", "num_behaviours_to_select"), &UtilityAIAgent::set_num_behaviours_to_select);
    ClassDB::bind_method(D_METHOD("get_num_behaviours_to_select"), &UtilityAIAgent::get_num_behaviours_to_select);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "num_behaviours_to_select", PROPERTY_HINT_RANGE, "1,16"), "set_num_behaviours_to_select","get_num_behaviours_to_select");

    ClassDB::bind_method(D_METHOD("set_thinking_delay_in_seconds", "thinking_delay_in_seconds"), &UtilityAIAgent::set_thinking_delay_in_seconds);
    ClassDB::bind_method(D_METHOD("get_thinking_delay_in_seconds"), &UtilityAIAgent::get_thinking_delay_in_seconds);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "thinking_delay_in_seconds", PROPERTY_HINT_RANGE, "0.0,3600.0,or_greater,suffix:seconds"), "set_thinking_delay_in_seconds","get_thinking_delay_in_seconds");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_top_scoring_behaviour_name", "top_scoring_behaviour_name"), &UtilityAIAgent::set_top_scoring_behaviour_name);
    ClassDB::bind_method(D_METHOD("get_top_scoring_behaviour_name"), &UtilityAIAgent::get_top_scoring_behaviour_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "top_scoring_behaviour_name", PROPERTY_HINT_NONE), "set_top_scoring_behaviour_name","get_top_scoring_behaviour_name");

    ClassDB::bind_method(D_METHOD("set_current_behaviour_name", "current_behaviour_name"), &UtilityAIAgent::set_current_behaviour_name);
    ClassDB::bind_method(D_METHOD("get_current_behaviour_name"), &UtilityAIAgent::get_current_behaviour_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "current_behaviour_name", PROPERTY_HINT_NONE), "set_current_behaviour_name","get_current_behaviour_name");

    ClassDB::bind_method(D_METHOD("set_total_evaluate_options_usec", "total_evaluate_options_usec"), &UtilityAIAgent::set_total_evaluate_options_usec);
    ClassDB::bind_method(D_METHOD("get_total_evaluate_options_usec"), &UtilityAIAgent::get_total_evaluate_options_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_evaluate_options_usec", PROPERTY_HINT_NONE), "set_total_evaluate_options_usec","get_total_evaluate_options_usec");


    // Add all signals.

    ADD_SIGNAL(MethodInfo("behaviour_changed", PropertyInfo(Variant::OBJECT, "behaviour_node")));
    //ADD_SIGNAL(MethodInfo("behaviour_completed", PropertyInfo(Variant::OBJECT, "behaviour_node")));
    ADD_SIGNAL(MethodInfo("action_changed", PropertyInfo(Variant::OBJECT, "action_node")));
}


// Constructor and destructor.

UtilityAIAgent::UtilityAIAgent() {
    _current_behaviour_node = nullptr;
    _num_behaviours_to_select = 1;
    _num_possible_behaviours = 0;
    for( int i = 0; i < UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS; ++i ) {
        //_top_scoring_behaviours[i] = -1;
        _top_scoring_behaviours_score[i] = 0.0;
        _top_scoring_behaviours_nodes[i] = nullptr;
    }
    _top_scoring_behaviour_name = "";
    
    _current_action_node = nullptr;

    _thinking_delay_in_seconds = 1.0; // One second delay in thinking of options.
    _thinking_delay_in_seconds_current_timer = 0.0; 

    _rng.set_seed(time(0));

    _total_evaluate_options_usec = 0;

    
}


UtilityAIAgent::~UtilityAIAgent() {
    _current_behaviour_node = nullptr;
    _current_action_node = nullptr;
    for( int i = 0; i < UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS; ++i ) {
        _top_scoring_behaviours_nodes[i] = nullptr;
    }
}

// Handling functions.

void UtilityAIAgent::evaluate_options(double delta) { 
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    int num_children = get_child_count();
    if( num_children < 1 ) return; // Cannot evaluate without children.

    if( _current_behaviour_node != nullptr ) {
        // Respect the thinking delay if we have a current behaviour.
        _thinking_delay_in_seconds_current_timer -= delta;
        if( _thinking_delay_in_seconds_current_timer > 0.0 ) return;
        _thinking_delay_in_seconds_current_timer = _thinking_delay_in_seconds;

        // If the current behaviour cannot be interrupted, don't evaluate.
        UtilityAIBehaviour* behaviour_node = godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node);
        if( !behaviour_node->get_can_be_interrupted() ) {
            _total_evaluate_options_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_usec(_total_evaluate_options_usec);
            return;
        }
    }

    // Go through the behaviours and check which one seems
    // best to perform.
    double score = 0.0;
    int place_in_behaviour_list = 0;
    _num_possible_behaviours = 0;
    int chosen_node_index = 0;
    float highest_score = -1.0f;
    UtilityAIBehaviour* new_behaviour = nullptr;

    for( int b = 0; b < _num_behaviours_to_select; ++b ) {
        _top_scoring_behaviours_nodes[b] = nullptr;
        _top_scoring_behaviours_score[b] = -1.0;
    }
    
    // Evaluate the children.
    for( int i = 0; i < num_children; ++i ) {
        Node* node = get_child(i);
        if( node == nullptr ) continue;

        // If it is a sensor, do an evaluation to update any groups.
        UtilityAISensors* sensorNode = godot::Object::cast_to<UtilityAISensors>(node);
        if( sensorNode != nullptr ) {
            if( sensorNode->get_is_active() ) {
                sensorNode->evaluate_sensor_value();
            }
            sensorNode = nullptr;
            continue;
        }

        // If it is a behaviour group, see if it evaluates so that it should be used.
        UtilityAIBehaviourGroup* behaviourGroupNode = godot::Object::cast_to<UtilityAIBehaviourGroup>(node);
        if( behaviourGroupNode != nullptr ) {
            bool is_behaviour_group_valid = behaviourGroupNode->evaluate();//this);
            if( is_behaviour_group_valid ) {
                // Go through the group children and find their place in the top_n list.
                for( int bgi = 0; bgi < behaviourGroupNode->get_child_count(); ++bgi ) {
                    Node* bgiNode = behaviourGroupNode->get_child(bgi);
                    if(bgiNode == nullptr ) continue;
                    UtilityAIBehaviour* bgiBehaviourNode = godot::Object::cast_to<UtilityAIBehaviour>(bgiNode);
                    if( bgiBehaviourNode == nullptr ) continue;
                    if( !bgiBehaviourNode->get_is_active()) continue;

                    score = bgiBehaviourNode->evaluate();//this);
                    if( score > 0.0 ) {
                        place_into_top_n_behaviour_list( bgiBehaviourNode, score );
                    }
                }//endfor behaviour group children
            }//endif behaviour group is valid
            continue;
        }//endif behaviour group node

        // If it is a behaviour, evaluate it and place in to the top_n list.
        UtilityAIBehaviour* behaviourNode = godot::Object::cast_to<UtilityAIBehaviour>(node);
        if( behaviourNode == nullptr ) continue;
        if( !behaviourNode->get_is_active()) continue;

        score = behaviourNode->evaluate();//this);
        if( score > 0.0 ) {
            place_into_top_n_behaviour_list( behaviourNode, score );
        }
    }//endfor children

    if( _num_possible_behaviours < 1 ) {
        if( _current_behaviour_node != nullptr ){
            (godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->end_behaviour();
            _current_behaviour_node = nullptr;
        }
        //WARN_PRINT("UtilityAIAgent::evaluate_options(): Error, agent could not find valid behaviours!");
        _total_evaluate_options_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        return; // No behaviour chosen.
    }

    _top_scoring_behaviour_name = "";
    if( _top_scoring_behaviours_nodes[0] != nullptr ) {
        _top_scoring_behaviour_name = _top_scoring_behaviours_nodes[0]->get_name();
    }

    int chosen_behaviour_index = 0;
    if( _num_possible_behaviours > 1 ) {
        int random_behaviour = _rng.randi_range(0, _num_possible_behaviours-1);
        chosen_behaviour_index = random_behaviour;
    }
    
    new_behaviour = godot::Object::cast_to<UtilityAIBehaviour>(_top_scoring_behaviours_nodes[chosen_behaviour_index]);
    ERR_FAIL_COND_MSG( new_behaviour == nullptr, "UtilityAIAgent::evaluate_options(): Error, new_behaviour is nullptr.");

    if( new_behaviour == _current_behaviour_node ) return; // No change.
    if( _current_action_node != nullptr ) {
        (godot::Object::cast_to<UtilityAIActions>(_current_action_node))->end_action();   
        _current_action_node = nullptr;
    }
    if( _current_behaviour_node != nullptr ) {
        (godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->end_behaviour();   
        _current_behaviour_node = nullptr;
    }

    // Start and signal the chosen behaviour node.
    _current_behaviour_name = new_behaviour->get_name();
    _current_behaviour_node = godot::Object::cast_to<Node>(new_behaviour);
    new_behaviour->start_behaviour();
    _current_action_node = nullptr; 
    emit_signal("behaviour_changed", _current_behaviour_node);
    emit_signal("action_changed", _current_action_node);

    _thinking_delay_in_seconds_current_timer = _thinking_delay_in_seconds;
    
    _total_evaluate_options_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_ai_agents_usec(_total_evaluate_options_usec);
}


void UtilityAIAgent::place_into_top_n_behaviour_list(Node* behaviour, float score ) {
    
    // First on the list.
    if( _num_possible_behaviours == 0 ) {
        _top_scoring_behaviours_nodes[0] = behaviour;
        _top_scoring_behaviours_score[0] = score;
        _num_possible_behaviours = 1;
        return;
    }

    // Somewhere in the list.
    int place_in_behaviour_list = -1;
    for( int b = 0; b < _num_behaviours_to_select; ++b ) {
        if( score > _top_scoring_behaviours_score[b]) {
            place_in_behaviour_list = b;
            break;
        }
    }
    if( place_in_behaviour_list < 0 ) return; // Not better than anything else on the list.

    
    // Last on the list.
    if( place_in_behaviour_list == _num_behaviours_to_select-1 ) {
        _top_scoring_behaviours_nodes[_num_behaviours_to_select-1] = behaviour;
        _top_scoring_behaviours_score[_num_behaviours_to_select-1] = score;
        return;
    }

    // In the beginning or in the middle of a list.
    for( int b = _num_behaviours_to_select-1; b > place_in_behaviour_list; --b ) {
        _top_scoring_behaviours_nodes[b] = _top_scoring_behaviours_nodes[b-1];
        _top_scoring_behaviours_score[b] = _top_scoring_behaviours_score[b-1];
    }
    
    _top_scoring_behaviours_nodes[place_in_behaviour_list] = behaviour;
    _top_scoring_behaviours_score[place_in_behaviour_list] = score;
    if(_num_possible_behaviours < _num_behaviours_to_select ) {
        ++_num_possible_behaviours;
    }

}


void UtilityAIAgent::update_current_behaviour() {
    if( _current_behaviour_node == nullptr ){
        // No behaviour, so make sure the current action node is null as well.
        if( _current_action_node != nullptr ) {
            UtilityAIActions* actions_node = godot::Object::cast_to<UtilityAIActions>(_current_action_node);
            if( actions_node != nullptr ) {
                actions_node->end_action();
            }
            _current_action_node = nullptr;
            emit_signal("action_changed", _current_action_node );    
        }
        return;
    } 
    Node* new_action_node = godot::Object::cast_to<Node>((godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->update_behaviour());
    if( _current_action_node != new_action_node ) {
        _current_action_node = new_action_node;
        emit_signal("action_changed", _current_action_node );
    }
    if( _current_action_node == nullptr ) {
        (godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->end_behaviour();
        _current_behaviour_name = "";
        //emit_signal("behaviour_completed", _current_behaviour_node );
        _current_behaviour_node = nullptr;
        emit_signal("behaviour_changed", _current_behaviour_node );
    }
}


void UtilityAIAgent::set_current_action_is_finished(bool is_finished) {
    if( _current_behaviour_node == nullptr ) return;
    if( _current_action_node == nullptr ) return;
    ((UtilityAIAction*)_current_action_node)->set_is_finished(is_finished);
}


void UtilityAIAgent::abort_current_behaviour() {
    if( _current_behaviour_node == nullptr ) return;
    (godot::Object::cast_to<UtilityAIBehaviour>(_current_behaviour_node))->end_behaviour();
    _current_behaviour_name = "";
    _current_behaviour_node = nullptr;
    _current_action_node = nullptr;    
    emit_signal("behaviour_changed", _current_behaviour_node);
    emit_signal("action_changed", _current_action_node );
}


// Getters and Setters.

void UtilityAIAgent::set_current_behaviour_name( godot::String current_behaviour_name ) {
    _current_behaviour_name = current_behaviour_name;
}

godot::String UtilityAIAgent::get_current_behaviour_name() const {
    return _current_behaviour_name;
}

void UtilityAIAgent::set_current_behaviour_node( Node* new_behaviour ) {
    _current_behaviour_node = new_behaviour;
}

Node* UtilityAIAgent::get_current_behaviour_node() const {
    return _current_behaviour_node;
}

void  UtilityAIAgent::set_current_action_node( Node* new_action_node ) {
    _current_action_node = new_action_node;
}

Node* UtilityAIAgent::get_current_action_node() const {
    return _current_action_node;
}

void UtilityAIAgent::set_num_behaviours_to_select( int num_behaviours_to_select ) {
    _num_behaviours_to_select = num_behaviours_to_select;
}

int  UtilityAIAgent::get_num_behaviours_to_select() const {
    return _num_behaviours_to_select;
}

void UtilityAIAgent::set_thinking_delay_in_seconds( double thinking_delay_in_seconds ) {
    _thinking_delay_in_seconds = thinking_delay_in_seconds;
}

double UtilityAIAgent::get_thinking_delay_in_seconds() const {
    return _thinking_delay_in_seconds;
}


void UtilityAIAgent::set_top_scoring_behaviour_name( godot::String top_scoring_behaviour_name ) {
    _top_scoring_behaviour_name = top_scoring_behaviour_name;
}

godot::String UtilityAIAgent::get_top_scoring_behaviour_name() const {
    return _top_scoring_behaviour_name;
}

void UtilityAIAgent::set_total_evaluate_options_usec( uint64_t total_evaluate_options_usec ) {
    _total_evaluate_options_usec = total_evaluate_options_usec;
}

uint64_t UtilityAIAgent::get_total_evaluate_options_usec() const {
    return _total_evaluate_options_usec;
}


/**
void UtilityAIAgent::set_random_number_generator( RandomNumberGenerator rng ) {
    _rng = rng;
}

RandomNumberGenerator UtilityAIAgent::get_random_number_generator() const {
    return _rng;
}
*/