#include "root.h"
#include "nodes.h"
#include "../sensors.h"

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

UtilityAIStateTreeNodes* UtilityAISTRoot::get_active_state() const {
    return _active_state;
}


// Handling functions.


UtilityAIStateTreeNodes* UtilityAISTRoot::tick(Variant user_data, double delta) { 
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    
    if( _active_state ) {
        // Tick the active state.
        _active_state->tick(user_data, delta);
    }
    if( !get_is_active() ){
        _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
        return nullptr;
    } 
    if( Engine::get_singleton()->is_editor_hint() ) {
        _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_behaviour_trees_usec(_total_tick_usec);
        return nullptr;
    } 

    
    for( int i = 0; i < get_child_count(); ++i ) {
        Node* node = get_child(i);
        if( UtilityAISensors* sensor = godot::Object::cast_to<UtilityAISensors>(node) ) {
            if( !sensor-> get_is_active() ) {
                continue;
            }
            sensor->evaluate_sensor_value();
            continue;
        }
        UtilityAIStateTreeNodes* result_state = nullptr;
        if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(node) ) {
            if( !stnode->get_is_active() ) {
                continue;
            } 
            result_state = stnode->tick(user_data, delta);
            
            _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_tick_usec);
            return result_state;
        }
    }
    _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    UtilityAIPerformanceMonitorSingleton::get_singleton()->increment_total_time_elapsed_state_trees_usec(_total_tick_usec);
    return nullptr; // We shouldn't get here. If we do, there were no child nodes.
}


// Godot virtuals.
void UtilityAISTRoot::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    reset();
}


