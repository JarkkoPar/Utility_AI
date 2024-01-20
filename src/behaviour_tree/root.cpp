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

void UtilityAIBTRoot::_bind_methods() {
    #ifdef DEBUG_ENABLED
    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_total_tick_usec", "total_tick_usec"), &UtilityAIBTRoot::set_total_tick_usec);
    ClassDB::bind_method(D_METHOD("get_total_tick_usec"), &UtilityAIBTRoot::get_total_tick_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_tick_usec", PROPERTY_HINT_NONE), "set_total_tick_usec","get_total_tick_usec");
    #endif
    ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAIBTRoot::tick);
}


// Constructor and destructor.

UtilityAIBTRoot::UtilityAIBTRoot() {
    #ifdef DEBUG_ENABLED
    _total_tick_usec = 0;
    #endif
}


UtilityAIBTRoot::~UtilityAIBTRoot() {
}


// Getters and Setters.

#ifdef DEBUG_ENABLED
void UtilityAIBTRoot::set_total_tick_usec( uint64_t total_tick_usec ) {
    _total_tick_usec = total_tick_usec;
}

uint64_t  UtilityAIBTRoot::get_total_tick_usec() const {
    return _total_tick_usec;
}
#endif



// Handling functions.


int UtilityAIBTRoot::tick(Variant user_data, float delta) { 
    #ifdef DEBUG_ENABLED
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    #endif
    if( !get_is_active() ){
        #ifdef DEBUG_ENABLED
        _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
        #endif
        return BT_FAILURE;
    } 
    if( Engine::get_singleton()->is_editor_hint() ) {
        #ifdef DEBUG_ENABLED
        _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
        #endif
        return BT_FAILURE;
    } 

    if(get_reset_rule() == UtilityAIBehaviourTreeNodesResetRule::NEVER) {
        if( get_internal_status() == BT_INTERNAL_STATUS_COMPLETED ){
            #ifdef DEBUG_ENABLED
            _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
            #endif
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
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(node) ) {
            if( !btnode->get_is_active() ) {
                continue;
            } 
            int result = btnode->tick(user_data, delta);
            set_tick_result(result);
            if( btnode->get_internal_status() == BT_INTERNAL_STATUS_COMPLETED ) {
                set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
            }
            #ifdef DEBUG_ENABLED
            _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
            #endif
            return result;
        }
    }
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    #ifdef DEBUG_ENABLED
    _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
    #endif
    return BT_FAILURE; // We shouldn't get here. If we do, there were no child nodes.
}


// Godot virtuals.
void UtilityAIBTRoot::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
#ifdef DEBUG_ENABLED
    UtilityAILiveDebugger::get_singleton()->register_behaviour_tree(this->get_instance_id());
#endif
    reset();
}


