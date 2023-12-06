#include "UtilityAIBTLimiter.h"
#include "UtilityAIBehaviourTreeNodes.h"
#include "../UtilityAISensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTLimiter::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_max_repeat_times", "repeat_times"), &UtilityAIBTLimiter::set_max_repeat_times);
    ClassDB::bind_method(D_METHOD("get_max_repeat_times"), &UtilityAIBTLimiter::get_max_repeat_times);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_repeat_times", PROPERTY_HINT_RANGE, "0,100,or_greater"), "set_max_repeat_times","get_max_repeat_times");

    ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIBTLimiter::set_reset_rule);
    ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIBTLimiter::get_reset_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");
 
}


// Constructor and destructor.

UtilityAIBTLimiter::UtilityAIBTLimiter() {
    _max_repeat_times = 3;
    _current_repeat_times = -1;
}


UtilityAIBTLimiter::~UtilityAIBTLimiter() {
}


// Getters and Setters.


void UtilityAIBTLimiter::set_max_repeat_times( int max_repeat_times ) {
    _max_repeat_times = max_repeat_times;
}

int UtilityAIBTLimiter::get_max_repeat_times() const {
    return _max_repeat_times;
}

/**
void UtilityAIBTLimiter::set_tick_result( int tick_result ) {
    _tick_result = tick_result;
    if( _tick_result > 1 ) {
        _tick_result = 1;
    } else if (_tick_result < -1 ) {
        _tick_result = -1;
    }
}


int  UtilityAIBTLimiter::get_tick_result() const {
    return _tick_result;
}

/**/

// Handling functions.


void UtilityAIBTLimiter::reset_bt_node() {
    _current_repeat_times = _max_repeat_times;
}


int UtilityAIBTLimiter::tick(Variant user_data, double delta) { 
    //if( !get_is_active() ) return BT_SKIP;
    if( Engine::get_singleton()->is_editor_hint() ) return BT_FAILURE;
    if( get_internal_status() == BT_INTERNAL_STATUS_UNTICKED ) {
        reset_bt_node();
    }
    
    
    if( _current_repeat_times == 0 ){
        set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
        set_tick_result(BT_FAILURE);
        return BT_FAILURE;
    } 
    
    set_internal_status(BT_INTERNAL_STATUS_TICKED);

    for( int i = 0; i < get_child_count(); ++i ) {
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i)) ) {
            if( !btnode->get_is_active() ) {
                continue;
            } 
            --_current_repeat_times;
            int result = btnode->tick(user_data, delta);
            set_tick_result(result);
            if( result != BT_RUNNING ) {
                return result;
            }
        }
    }
    // If we get here, there are no child nodes set.
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);   
    set_tick_result(BT_FAILURE);
    return BT_FAILURE;
}


