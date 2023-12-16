#include "transition.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include "../performance_monitor_singleton.h"


using namespace godot;

// Method binds.

void UtilityAISTTransition::_bind_methods() {

    //ADD_SUBGROUP("Debugging","");

    //ClassDB::bind_method(D_METHOD("set_total_tick_usec", "total_tick_usec"), &UtilityAISTTransition::set_total_tick_usec);
    //ClassDB::bind_method(D_METHOD("get_total_tick_usec"), &UtilityAISTTransition::get_total_tick_usec);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "total_tick_usec", PROPERTY_HINT_NONE), "set_total_tick_usec","get_total_tick_usec");

    //ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAISTTransition::tick);
}


// Constructor and destructor.

UtilityAISTTransition::UtilityAISTTransition() {
    
}


UtilityAISTTransition::~UtilityAISTTransition() {
}


// Getters and Setters.


void UtilityAISTTransition::set_target_state( UtilityAIStateTreeNodes* target_state ) {
    _target_state = target_state;
}


UtilityAIStateTreeNodes* UtilityAISTTransition::get_target_state() const {
    return _target_state;
}


// Handling functions.


UtilityAIStateTreeNodes* UtilityAISTTransition::tick(Variant user_data, double delta) { 
    /**
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    if( !get_is_active() ){
        _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
        return BT_FAILURE;
    } 
    if( Engine::get_singleton()->is_editor_hint() ) {
        _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
        return BT_FAILURE;
    } 

    if(get_reset_rule() == UtilityAIStateTreeNodesResetRule::NEVER) {
        if( get_internal_status() == BT_INTERNAL_STATUS_COMPLETED ){
            _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
            return get_tick_result();
        }  
    } 
    
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    
    for( int i = 0; i < get_child_count(); ++i ) {
        Node* node = get_child(i);
        if( UtilityAISensors* sensor = godot::Object::cast_to<UtilityAISensors>(node) ) {
            if( !sensor-> get_is_active() ) {
                continue;
            }
            sensor->evaluate_sensor_value();
            continue;
        }
        if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(node) ) {
            if( !stnode->get_is_active() ) {
                continue;
            } 
            int result = stnode->tick(user_data, delta);
            set_tick_result(result);
            if( stnode->get_internal_status() == BT_INTERNAL_STATUS_COMPLETED ) {
                set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
            }
            _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
            return result;
        }
    }
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
    /**/
    return nullptr; // We shouldn't get here. If we do, there were no child nodes.
}


// Godot virtuals.
void UtilityAISTTransition::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    reset();
}


