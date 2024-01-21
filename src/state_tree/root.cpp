#include "root.h"
#include "nodes.h"
#include "../agent_behaviours/sensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include "../performance_monitor_singleton.h"
#ifdef DEBUG_ENABLED
#include "../debugger/live_debugger.h"
#endif


using namespace godot;

// Method binds.

void UtilityAISTRoot::_bind_methods() {
    #ifdef DEBUG_ENABLED
    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_total_tick_usec", "total_tick_usec"), &UtilityAISTRoot::set_total_tick_usec);
    ClassDB::bind_method(D_METHOD("get_total_tick_usec"), &UtilityAISTRoot::get_total_tick_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_tick_usec", PROPERTY_HINT_NONE), "set_total_tick_usec","get_total_tick_usec");
    #endif

    ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAISTRoot::tick);
}


// Constructor and destructor.

UtilityAISTRoot::UtilityAISTRoot() {
    #ifdef DEBUG_ENABLED
    _total_tick_usec = 0;
    _total_transition_usec = 0;
    #endif
}


UtilityAISTRoot::~UtilityAISTRoot() {
}


// Getters and Setters.

#ifdef DEBUG_ENABLED
void UtilityAISTRoot::set_total_tick_usec( uint64_t total_tick_usec ) {
    _total_tick_usec = total_tick_usec;
}

uint64_t  UtilityAISTRoot::get_total_tick_usec() const {
    return _total_tick_usec;
}
#endif

// Handling methods.

void UtilityAISTRoot::transition_to( NodePath path_to_node, Variant user_data, float delta ) {
    UtilityAIStateTreeNodes* new_state = get_node<UtilityAIStateTreeNodes>(path_to_node);
    if( new_state == nullptr ){
        return;
    } 
    bool result = try_transition(new_state, user_data, delta );
}


bool UtilityAISTRoot::try_transition( UtilityAIStateTreeNodes* transition_target_node, Variant user_data, float delta) {
    #ifdef DEBUG_ENABLED
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    #endif
    // Check that this is a valid transition for this tree.
    if( transition_target_node == nullptr ){
        #ifdef DEBUG_ENABLED
        _total_transition_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_transition_usec);
        #endif
        return false;
    } 
    if( !get_is_active() ){
        #ifdef DEBUG_ENABLED
        _total_transition_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_transition_usec);
        #endif
        return false;
    } 
    if( Engine::get_singleton()->is_editor_hint() ) {
        #ifdef DEBUG_ENABLED
        _total_transition_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_transition_usec);
        #endif
        return false;
    } 
    bool new_state_found = false;
    if( UtilityAIStateTreeNodes* new_state = transition_target_node->evaluate_state_activation(user_data, delta) ) {
        // We got a new leaf state. Get the new state list.
        _active_states_vector.clear();  
        TypedArray<UtilityAIStateTreeNodes> new_active_states;
        std::vector<bool> is_existing_state;// = new std::vector<bool>();
        Node* cur_state = new_state;
        while( cur_state != this ) {
            new_active_states.push_back(cur_state);
            is_existing_state.push_back(_active_states.has(cur_state));
            _active_states_vector.push_back(godot::Object::cast_to<UtilityAIStateTreeNodes>(cur_state));

            cur_state = cur_state->get_parent();
        }

        // Now that we have the new states in the list, do on_exit to those that
        // are leaving the list.
        for( int i = 0; i < _active_states_vector.size(); ++i ) {
            UtilityAIStateTreeNodes* cur_active_state = _active_states_vector[i]; //godot::Object::cast_to<UtilityAIStateTreeNodes>(_active_states[i]);
            if( !new_active_states.has(cur_active_state) ) {
                cur_active_state->on_exit_state(user_data, delta);
            }
        }

        // And then enter the new states.
        _active_states = new_active_states;
        for( int i = _active_states_vector.size() - 1; i > -1; --i ) {
            if( !is_existing_state[i] ) {
                //UtilityAIStateTreeNodes* cur_active_state = godot::Object::cast_to<UtilityAIStateTreeNodes>(_active_states[i]);
                //cur_active_state->on_enter_state(user_data, delta);
                _active_states_vector[i]->on_enter_state(user_data, delta);
            }
        }
        new_state_found = true;
    }//endif new state found
    #ifdef DEBUG_ENABLED
    _total_transition_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_transition_usec);
    #endif
    return new_state_found;

}

void UtilityAISTRoot::tick(Variant user_data, float delta) { 
    #ifdef DEBUG_ENABLED
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    #endif

    // No states, so try transition to the root.
    if( _active_states_vector.size() == 0 ) {
        try_transition(this, user_data, delta);
    }

    // Update the sensors.
    //for( int i = 0; i < get_child_count(); ++i ) {
    //    Node* node = get_child(i);
    //    if( UtilityAISensors* sensor = godot::Object::cast_to<UtilityAISensors>(node) ) {
    for( unsigned int i = 0; i < _num_child_sensors; ++i ) {
        UtilityAISensors* sensor = _child_sensors[i];
        if( !sensor-> get_is_active() ) {
            continue;
        }
        sensor->evaluate_sensor_value();
    //    } else {
    //        break; // No more sensors.
    //    }
    }//endfor sensors
    

    // If there are active states, tick their custom method from the 
    // root to the active leaf.
    if( _active_states_vector.size() > 0 ) {
        for( int i = _active_states_vector.size()-1; i > -1; --i ) {
            UtilityAIStateTreeNodes* stnode = _active_states_vector[i];

            //if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(_active_states[i]) ) {
            stnode->on_tick(user_data, delta);
            //}
        }
    }
    #ifdef DEBUG_ENABLED
    _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_tick_usec);
    #endif
}

// Godot virtuals.

/**/
void UtilityAISTRoot::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    set_root_node(this);
    _child_sensors.clear();
    for( int i = 0; i < get_child_count(); ++i ) {
        if( UtilityAISensors* sensor = godot::Object::cast_to<UtilityAISensors>(get_child(i)) ) {
            _child_sensors.push_back(sensor);
        }
    }
    _num_child_sensors = (unsigned int)_child_sensors.size();
#ifdef DEBUG_ENABLED
    //UtilityAILiveDebugger::get_singleton()->register_state_tree(this->get_instance_id());
    //WARN_PRINT("ST Registered!");
#endif
}
/**/

