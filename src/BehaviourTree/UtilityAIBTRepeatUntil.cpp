#include "UtilityAIBTRepeatUntil.h"
#include "UtilityAIBehaviourTreeNodes.h"
#include "../UtilityAISensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTRepeatUntil::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_max_repeat_times", "max_repeat_times"), &UtilityAIBTRepeatUntil::set_max_repeat_times);
    ClassDB::bind_method(D_METHOD("get_max_repeat_times"), &UtilityAIBTRepeatUntil::get_max_repeat_times);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_repeat_times", PROPERTY_HINT_RANGE, "-1,100,or_greater"), "set_max_repeat_times","get_max_repeat_times");

    ClassDB::bind_method(D_METHOD("set_expected_tick_result", "expected_tick_result"), &UtilityAIBTRepeatUntil::set_expected_tick_result);
    ClassDB::bind_method(D_METHOD("get_expected_tick_result"), &UtilityAIBTRepeatUntil::get_expected_tick_result);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "expected_tick_result", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_expected_tick_result","get_expected_tick_result");

    ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIBTRepeatUntil::set_reset_rule);
    ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIBTRepeatUntil::get_reset_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");
 
}


// Constructor and destructor.

UtilityAIBTRepeatUntil::UtilityAIBTRepeatUntil() {
    _max_repeat_times = 3;
    _current_max_repeat_times = -1;
    _expected_tick_result = BT_SUCCESS;
}


UtilityAIBTRepeatUntil::~UtilityAIBTRepeatUntil() {
}


// Getters and Setters.


void UtilityAIBTRepeatUntil::set_max_repeat_times( int max_repeat_times ) {
    _max_repeat_times = max_repeat_times;
}

int UtilityAIBTRepeatUntil::get_max_repeat_times() const {
    return _max_repeat_times;
}



void UtilityAIBTRepeatUntil::set_expected_tick_result( int expected_tick_result ) {
    _expected_tick_result = expected_tick_result;
    if( _expected_tick_result > 1 ) {
        _expected_tick_result = 1;
    } else if (_expected_tick_result < -1 ) {
        _expected_tick_result = -1;
    }
}


int  UtilityAIBTRepeatUntil::get_expected_tick_result() const {
    return _expected_tick_result;
}



// Handling functions.

void UtilityAIBTRepeatUntil::reset_bt_node() {
    _current_max_repeat_times = _max_repeat_times;
}


int UtilityAIBTRepeatUntil::tick(Variant user_data, double delta) { 
    if( !get_is_active() ) return BT_FAILURE;
    if( Engine::get_singleton()->is_editor_hint() ) return BT_FAILURE;

    if( get_internal_status() == BT_INTERNAL_STATUS_UNTICKED && _max_repeat_times > 0 ) {
        reset_bt_node();
    }
    
    if( _current_max_repeat_times == 0 ) {
        set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
        set_tick_result(_expected_tick_result);
        return _expected_tick_result;
    }

    set_internal_status(BT_INTERNAL_STATUS_TICKED);

    for( int i = 0; i < get_child_count(); ++i ) {
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i)) ) {
            if( !btnode->get_is_active() ) {
                continue;
            } 
            if( _max_repeat_times > -1 ) {
                --_current_max_repeat_times;
            }
            int result = btnode->tick(user_data, delta);
            if( result == _expected_tick_result ) {
                set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
                set_tick_result(BT_SUCCESS);
                return BT_SUCCESS;
            } 
            set_tick_result(BT_RUNNING);
            return BT_RUNNING;
        }
    }
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    set_tick_result(BT_FAILURE);
    return BT_FAILURE;
}


