#include "repeater.h"
#include "nodes.h"
//#include "../sensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTRepeater::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_repeat_times", "repeat_times"), &UtilityAIBTRepeater::set_repeat_times);
    ClassDB::bind_method(D_METHOD("get_repeat_times"), &UtilityAIBTRepeater::get_repeat_times);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "repeat_times", PROPERTY_HINT_RANGE, "-1,100,or_greater"), "set_repeat_times","get_repeat_times");

    //ClassDB::bind_method(D_METHOD("set_current_repeat_times", "current_repeat_times"), &UtilityAIBTRepeater::set_current_repeat_times);
    //ClassDB::bind_method(D_METHOD("get_current_repeat_times"), &UtilityAIBTRepeater::get_current_repeat_times);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "current_repeat_times", PROPERTY_HINT_NONE ), "set_current_repeat_times","get_current_repeat_times");
    //ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIBTRepeater::set_reset_rule);
    //ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIBTRepeater::get_reset_rule);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");
    
}


// Constructor and destructor.

UtilityAIBTRepeater::UtilityAIBTRepeater() {
    _repeat_times = -1;
    _current_repeat_times = -1;
}


UtilityAIBTRepeater::~UtilityAIBTRepeater() {
}


// Getters and Setters.


void UtilityAIBTRepeater::set_repeat_times( int repeat_times ) {
    _repeat_times = repeat_times;
}

int UtilityAIBTRepeater::get_repeat_times() const {
    return _repeat_times;
}


void UtilityAIBTRepeater::set_current_repeat_times( int current_repeat_times ) {
    _current_repeat_times = current_repeat_times;
}

int UtilityAIBTRepeater::get_current_repeat_times() const {
    return _current_repeat_times;
}


/**
void UtilityAIBTRepeater::set_tick_result( int tick_result ) {
    _tick_result = tick_result;
    if( _tick_result > 1 ) {
        _tick_result = 1;
    } else if (_tick_result < -1 ) {
        _tick_result = -1;
    }
}


int  UtilityAIBTRepeater::get_tick_result() const {
    return _tick_result;
}
/**/


// Handling functions.

void UtilityAIBTRepeater::reset_bt_node() {
    _current_repeat_times = _repeat_times;
}

int UtilityAIBTRepeater::tick(Variant user_data, float delta) { 
    if( !get_is_active() ) return BT_FAILURE;
    if( Engine::get_singleton()->is_editor_hint() ) return BT_FAILURE;

    if( get_internal_status() == BT_INTERNAL_STATUS_UNTICKED ) {
        reset_bt_node();
    }
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    //if( _is_first_tick ) {
    //    _is_first_tick = false;
    //    emit_signal("btnode_entered", user_data, delta);
    //}

    if( _current_repeat_times == 0 ){
        set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
        set_tick_result(BT_SUCCESS);
        return BT_SUCCESS;
    }
    if( get_internal_status() == BT_INTERNAL_STATUS_COMPLETED ) {
        set_tick_result(BT_SUCCESS);
        return BT_SUCCESS;
    } 

    //emit_signal("btnode_ticked",user_data, delta);
    //for( int i = 0; i < get_child_count(); ++i ) {
    //    if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i)) ) {
    for( unsigned int i = 0; i < _num_child_btnodes; ++i ) {
        UtilityAIBehaviourTreeNodes* btnode = _child_btnodes[i];
        if( !btnode->get_is_active() ) {
            continue;
        } 
        --_current_repeat_times;
        btnode->tick(user_data, delta);
        break;
    //    }
    }
    if( _current_repeat_times > 0 || _current_repeat_times < 0 ) {
        set_tick_result(BT_RUNNING);
        return BT_RUNNING;
    } else if (_current_repeat_times == 0 ) {
        set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
        set_tick_result(BT_SUCCESS);
        //emit_signal("btnode_exited", user_data, delta);
        return BT_SUCCESS;
    }
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    set_tick_result(BT_FAILURE);
    //emit_signal("btnode_exited", user_data, delta);
    return BT_FAILURE;
}


