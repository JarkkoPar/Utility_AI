#include "UtilityAIBTRoot.h"
#include "UtilityAIBehaviourTreeNodes.h"
#include "../UtilityAISensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTRoot::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_total_tick_usec", "total_tick_usec"), &UtilityAIBTRoot::set_total_tick_usec);
    ClassDB::bind_method(D_METHOD("get_total_tick_usec"), &UtilityAIBTRoot::get_total_tick_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_tick_usec", PROPERTY_HINT_NONE), "set_total_tick_usec","get_total_tick_usec");

    ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAIBTRoot::tick);
}


// Constructor and destructor.

UtilityAIBTRoot::UtilityAIBTRoot() {
    _total_tick_usec = 0;
}


UtilityAIBTRoot::~UtilityAIBTRoot() {
}


// Getters and Setters.


void UtilityAIBTRoot::set_total_tick_usec( uint64_t total_tick_usec ) {
    _total_tick_usec = total_tick_usec;
}

uint64_t  UtilityAIBTRoot::get_total_tick_usec() const {
    return _total_tick_usec;
}




// Handling functions.


int UtilityAIBTRoot::tick(Variant user_data, double delta) { 
    if( !get_is_active() ) return BT_FAILURE;
    if( Engine::get_singleton()->is_editor_hint() ) return BT_FAILURE;

    if(get_reset_rule() == UtilityAIBehaviourTreeNodesResetRule::NEVER) {
        if( get_internal_status() == BT_INTERNAL_STATUS_COMPLETED ) return get_tick_result(); 
    } 
    
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
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
            set_tick_result(result);
            if( btnode->get_internal_status() == BT_INTERNAL_STATUS_COMPLETED ) {
                set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
            }
            _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            return result;
        }
    }
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    _total_tick_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
    return BT_FAILURE; // We shouldn't get here. If we do, there were no child nodes.
}


// Godot virtuals.
void UtilityAIBTRoot::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    reset();
}


