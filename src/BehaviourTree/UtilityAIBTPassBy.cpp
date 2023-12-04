#include "UtilityAIBTPassBy.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTPassBy::_bind_methods() {
    
    //ClassDB::bind_method(D_METHOD("set_tick_result", "tick_result"), &UtilityAIBTPassBy::set_tick_result);
    //ClassDB::bind_method(D_METHOD("get_tick_result"), &UtilityAIBTPassBy::get_tick_result);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "tick_result", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1" ), "set_tick_result","get_tick_result");

}


// Constructor and destructor.

UtilityAIBTPassBy::UtilityAIBTPassBy() {
    //_tick_result = 1;
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

int UtilityAIBTPassBy::tick(Variant user_data, double delta) { 
    // The passBy node just calls its tick and then ticks the first
    // behaviour tree node child and returns the result of the child.
    // Otherwise it returns what ever is set as the tick result property.
    if( has_method("tick")) {
        call("tick", user_data, delta);
    }
    return BT_SKIP;
}

