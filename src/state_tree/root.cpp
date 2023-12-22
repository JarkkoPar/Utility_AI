#include "root.h"
#include "nodes.h"
#include "../agent_behaviours/sensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include "../performance_monitor_singleton.h"


using namespace godot;

// Method binds.

void UtilityAISTRoot::_bind_methods() {

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_total_tick_usec", "total_tick_usec"), &UtilityAISTRoot::set_total_tick_usec);
    ClassDB::bind_method(D_METHOD("get_total_tick_usec"), &UtilityAISTRoot::get_total_tick_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_tick_usec", PROPERTY_HINT_NONE), "set_total_tick_usec","get_total_tick_usec");

    ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAISTRoot::tick);
}


// Constructor and destructor.

UtilityAISTRoot::UtilityAISTRoot() {
    _total_tick_usec = 0;
    _total_transition_usec = 0;
    //_state_tree_nodes = Dictionary();
}


UtilityAISTRoot::~UtilityAISTRoot() {
}


// Getters and Setters.


void UtilityAISTRoot::set_total_tick_usec( uint64_t total_tick_usec ) {
    _total_tick_usec = total_tick_usec;
}

uint64_t  UtilityAISTRoot::get_total_tick_usec() const {
    return _total_tick_usec;
}

// Handling methods.

void UtilityAISTRoot::transition_to( NodePath path_to_node, Variant user_data, double delta ) {
    UtilityAIStateTreeNodes* new_state = get_node<UtilityAIStateTreeNodes>(path_to_node);
    if( new_state == nullptr ){
        return;
    } 
    bool result = try_transition(new_state, user_data, delta );
}


bool UtilityAISTRoot::try_transition( UtilityAIStateTreeNodes* transition_target_node, Variant user_data, double delta) {
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    
    // Check that this is a valid transition for this tree.
    if( transition_target_node == nullptr ){
        _total_transition_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_transition_usec);
        return false;
    } 
    if( !get_is_active() ){
        _total_transition_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_transition_usec);
        return false;
    } 
    if( Engine::get_singleton()->is_editor_hint() ) {
        _total_transition_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_transition_usec);
        return false;
    } 
    bool new_state_found = false;
    if( UtilityAIStateTreeNodes* new_state = transition_target_node->evaluate_state_activation(user_data, delta) ) {
        // We got a new state. Get the new state list.
        TypedArray<UtilityAIStateTreeNodes> new_active_states;
        std::vector<bool> is_existing_state;// = new std::vector<bool>();
        Node* cur_state = new_state;
        while( cur_state != this ) {
            new_active_states.push_back(cur_state);
            is_existing_state.push_back(_active_states.has(cur_state));
            cur_state = cur_state->get_parent();
        }

        // Now that we have the new states in the list, do on_exit to those that
        // are leaving the list.
        //for( int i = _active_states.size() - 1; i > -1; --i ) {
        for( int i = 0; i < _active_states.size(); ++i ) {
            UtilityAIStateTreeNodes* cur_active_state = godot::Object::cast_to<UtilityAIStateTreeNodes>(_active_states[i]);
            if( !new_active_states.has(cur_active_state) ) {
                cur_active_state->on_exit_state(user_data, delta);
            }
        }

        // And then enter the new states.
        _active_states = new_active_states;
        for( int i = _active_states.size() - 1; i > -1; --i ) {
            if( !is_existing_state[i] ) {
                UtilityAIStateTreeNodes* cur_active_state = godot::Object::cast_to<UtilityAIStateTreeNodes>(_active_states[i]);
                cur_active_state->on_enter_state(user_data, delta);
            }
        }
        new_state_found = true;
    }//endif new state found
    
    _total_transition_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_transition_usec);
    return new_state_found;

}

void UtilityAISTRoot::tick(Variant user_data, double delta) { 
    //WARN_PRINT("root->tick()");
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    
    // No states, so try transition to the root.
    if( _active_states.size() == 0 ) {
        //WARN_PRINT("tick: trying transition to get active states...");
        try_transition(this, user_data, delta);
        //WARN_PRINT("tick: try transition completed!");
    }

    // If there are active states, tick their custom method from the 
    // root to the active leaf.
    if( _active_states.size() > 0 ) {
        //WARN_PRINT("tick: Ticking active states...");
        for( int i = _active_states.size()-1; i > -1; --i ) {
            if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(_active_states[i]) ) {
                //WARN_PRINT("Calling on tick... ");
                //WARN_PRINT(stnode->get_name());
                stnode->on_tick(user_data, delta);
            }
        }
        //WARN_PRINT("tick: ticking completed!");
    }
    
    _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_tick_usec);
}

// Godot virtuals.

/**/
void UtilityAISTRoot::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    set_root_node(this);
}
/**/

