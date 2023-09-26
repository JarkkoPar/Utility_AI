#include "UtilityAISensor.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAISensor::_bind_methods() {
    
    
}


// Constructor and destructor.

UtilityAISensor::UtilityAISensor() {
    
}


UtilityAISensor::~UtilityAISensor() {
}

// Handling functions.

double UtilityAISensor::evaluate_sensor_value() {
    return get_sensor_value();
}

// Getters and Setters.



/**


// Godot virtuals.
/**
void UtilityAISensor::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAISensor::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAISensor error, no child nodes (states) have been added to the UtilityAISensor '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAISensorState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAISensor error, the first child is not a UtilityAISensorState node.");
    _current_state->_enter_state();
}

void UtilityAISensor::_process(double delta ) {
    //if( _update_method != UtilityAISensor_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_Sensor(delta);
}

void UtilityAISensor::_physics_process(double delta ) {
    //if( _update_method != UtilityAISensor_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_Sensor(delta);
}

/**/
