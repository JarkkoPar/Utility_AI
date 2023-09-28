#include "UtilityAIAgent.h"
#include "UtilityAISensors.h"
#include "UtilityAIBehaviour.h"


#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIAgent::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("get_current_behaviour"), &UtilityAIAgent::get_current_behaviour);

    ClassDB::bind_method(D_METHOD("evaluate_options"), &UtilityAIAgent::evaluate_options);
    
    //ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &UtilityAIAgent::_update_current_state);
    /**/

    ClassDB::bind_method(D_METHOD("set_num_behaviours_to_select", "num_behaviours_to_select"), &UtilityAIAgent::set_num_behaviours_to_select);
    ClassDB::bind_method(D_METHOD("get_num_behaviours_to_select"), &UtilityAIAgent::get_num_behaviours_to_select);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "num_behaviours_to_select", PROPERTY_HINT_RANGE, "1,16"), "set_num_behaviours_to_select","get_num_behaviours_to_select");
    

    // Add all signals.

    ADD_SIGNAL(MethodInfo("behaviour_changed", PropertyInfo(Variant::OBJECT, "behaviour_node")));
}


// Constructor and destructor.

UtilityAIAgent::UtilityAIAgent() {
    _chosen_behaviour_node = nullptr;
    _num_behaviours_to_select = 1;
    for( int i = 0; i < UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS; ++i ) {
        _top_scoring_behaviours[i] = -1;
        _top_scoring_behaviours_score[i] = 0.0;
    }
}


UtilityAIAgent::~UtilityAIAgent() {
}

// Handling functions.

void UtilityAIAgent::evaluate_options() { //double delta) {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    // Go through the behaviours and check which one seems
    // best to perform.
    double score = 0.0;
    int place_in_behaviour_list = 0;
    int num_possible_behaviours = 0;
    int chosen_node_index = 0;
    float highest_score = -1.0f;
    UtilityAIBehaviour* new_behaviour = nullptr;
    
    // Evaluate the children.
    int num_children = get_child_count();
    if( num_children < 1 ) return; // Cannot evaluate without children.
    for( int i = 0; i < num_children; ++i ) {
        Node* node = get_child(i);

        // If it is a sensor, do an evaluation to update any groups.
        UtilityAISensors* sensorNode = godot::Object::cast_to<UtilityAISensors>(node);
        if( sensorNode != nullptr ) {
            sensorNode->evaluate_sensor_value();
            sensorNode = nullptr;
            continue;
        }

        // If it is a behaviour, handle it.
        UtilityAIBehaviour* behaviourNode = godot::Object::cast_to<UtilityAIBehaviour>(node);
        if( behaviourNode == nullptr ) continue;

        score = behaviourNode->evaluate();//this, delta);
        //if( i == 0 || score > highest_score ) {
        //    highest_score = score;
        //    chosen_node_index = i;
        //    new_behaviour = behaviourNode;

        // get place on the list.
        for( int b = 0; b < UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS; ++b ) {
            if( score > _top_scoring_behaviours_score[b]) {
                place_in_behaviour_list = b;
                break;
            }
        }

        if( place_in_behaviour_list == UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS-1 ) {
            _top_scoring_behaviours[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS-1] = i;
            _top_scoring_behaviours_score[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS-1] = score;
            continue;
        }

        // Todo: add to the behaviour node list. And add to the correct place in the list.
        for( int b = num_possible_behaviours; b > place_in_behaviour_list; --b ) {
            _top_scoring_behaviours[b] = _top_scoring_behaviours[b-1];
            _top_scoring_behaviours_score[b] = _top_scoring_behaviours_score[b-1];
        }
        _top_scoring_behaviours[0] = i;
        _top_scoring_behaviours_score[0] = score;
        if(num_possible_behaviours < UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS-1 ) {
            ++num_possible_behaviours;
        }

    }//endfor children

    if( new_behaviour == nullptr || num_possible_behaviours < 1 ) {
        return; // No behaviour chosen.
    }

    // Pick a random behaviour.
    RandomNumberGenerator rnd;
    int random_behaviour = rnd.randi_range(0, num_possible_behaviours);
    new_behaviour = godot::Object::cast_to<UtilityAIBehaviour>(get_child(_top_scoring_behaviours[random_behaviour]));

    if( _chosen_behaviour_node != nullptr ) {
        ((UtilityAIBehaviour *)_chosen_behaviour_node)->end_behaviour();
    }

    // Start and signal the chosen behaviour node.
    new_behaviour->start_behaviour();
    _chosen_behaviour_node = new_behaviour;
    emit_signal("behaviour_changed", _chosen_behaviour_node);
}

// Getters and Setters.

void UtilityAIAgent::set_current_behaviour( Node* new_behaviour ) {
    if( _chosen_behaviour_node != nullptr ) {
        ((UtilityAIBehaviour *)_chosen_behaviour_node)->end_behaviour();
    }
    _chosen_behaviour_node = new_behaviour;
    if( _chosen_behaviour_node != nullptr ) {
        ((UtilityAIBehaviour *)_chosen_behaviour_node)->start_behaviour();
    }
}

Node* UtilityAIAgent::get_current_behaviour() const {
    return _chosen_behaviour_node;
}


void UtilityAIAgent::set_num_behaviours_to_select( int num_behaviours_to_select ) {
    _num_behaviours_to_select = num_behaviours_to_select;
}

int  UtilityAIAgent::get_num_behaviours_to_select() const {
    return _num_behaviours_to_select;
}
    

// Godot virtuals.
/**
void UtilityAIAgent::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIAgent::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIAgent error, no child nodes (states) have been added to the UtilityAIAgent '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIAgentState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIAgent error, the first child is not a UtilityAIAgentState node.");
    _current_state->_enter_state();
}

void UtilityAIAgent::_process(double delta ) {
    //if( _update_method != UtilityAIAgent_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_UtilityAIAgents(delta);
}

void UtilityAIAgent::_physics_process(double delta ) {
    //if( _update_method != UtilityAIAgent_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_UtilityAIAgents(delta);
}

/**/
