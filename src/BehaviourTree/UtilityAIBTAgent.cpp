#include "UtilityAIBTAgent.h"
#include "UtilityAIBehaviourTreeNodes.h"
#include "../UtilityAISensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTAgent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_total_tick_usec", "total_tick_usec"), &UtilityAIBTAgent::set_total_tick_usec);
    ClassDB::bind_method(D_METHOD("get_total_tick_usec"), &UtilityAIBTAgent::get_total_tick_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_tick_usec", PROPERTY_HINT_NONE), "set_total_tick_usec","get_total_tick_usec");

    ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAIBTAgent::tick);
}


// Constructor and destructor.

UtilityAIBTAgent::UtilityAIBTAgent() {
    _total_tick_usec = 0;
}


UtilityAIBTAgent::~UtilityAIBTAgent() {
}


// Getters and Setters.


void UtilityAIBTAgent::set_total_tick_usec( uint64_t total_tick_usec ) {
    _total_tick_usec = total_tick_usec;
}

uint64_t  UtilityAIBTAgent::get_total_tick_usec() const {
    return _total_tick_usec;
}




// Handling functions.


int UtilityAIBTAgent::tick(Variant user_data, double delta) { 
    if( !get_is_active() ) return BT_FAILURE;
    if( Engine::get_singleton()->is_editor_hint() ) return BT_FAILURE;
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
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
            _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            return result;
        }
    }
    _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    return -1;
}


