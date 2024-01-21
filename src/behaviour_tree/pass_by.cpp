#include "pass_by.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTPassBy::_bind_methods() {
    
    //ClassDB::bind_method(D_METHOD("set_tick_result", "tick_result"), &UtilityAIBTPassBy::set_tick_result);
    //ClassDB::bind_method(D_METHOD("get_tick_result"), &UtilityAIBTPassBy::get_tick_result);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "tick_result", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_tick_result","get_tick_result");

    //ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTPassBy::tick);

}


// Constructor and destructor.

UtilityAIBTPassBy::UtilityAIBTPassBy() {
    //_tick_result = 1;
    _has_on_tick_method = false;
    _has_tick_method = false;
}


UtilityAIBTPassBy::~UtilityAIBTPassBy() {
}


// Getters and Setters.
/*
void UtilityAIBTPassBy::set_tick_result( int tick_result ) {
    _tick_result = tick_result;
    if( _tick_result > 1 ) {
        _tick_result = 1;
    } else if (_tick_result < -1 ) {
        _tick_result = -1;
    }
}


int  UtilityAIBTPassBy::get_tick_result() const {
    return _tick_result;
}
/**/

// Handling methods.

int UtilityAIBTPassBy::tick(Variant user_data, float delta) { 
    // The passBy node just calls its tick and then ticks the first
    // behaviour tree node child and returns the result of the child.
    // Otherwise it returns what ever is set as the tick result property.
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    //if( _is_first_tick ) {
    //    _is_first_tick = false;
    //    emit_signal("btnode_entered", user_data, delta);
    //}
    if( _has_on_tick_method ) {
        call("on_tick", user_data, delta);
        
        
    } else if( _has_tick_method ) {
        call("tick", user_data, delta);
        
    }
    //emit_signal("btnode_ticked", user_data, delta);
    set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
    //emit_signal("btnode_exited", user_data, delta);
    return BT_SKIP;
}

// Godot virtuals.

void UtilityAIBTPassBy::_notification(int p_what) {
    if( p_what == NOTIFICATION_POST_ENTER_TREE ){
        _has_on_tick_method = has_method("on_tick");
        _has_tick_method = has_method("tick");

    } else if ( p_what == NOTIFICATION_CHILD_ORDER_CHANGED ) {
        update_child_vectors();
    }
}

