#include "UtilityAISensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAISensors::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_sensor_value", "sensor_value"), &UtilityAISensors::set_sensor_value);
    ClassDB::bind_method(D_METHOD("get_sensor_value"), &UtilityAISensors::get_sensor_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sensor_value", PROPERTY_HINT_RANGE, "0.0,1.0,allow_greater,allow_lower"), "set_sensor_value","get_sensor_value");
    
}


// Constructor and destructor.

UtilityAISensors::UtilityAISensors() {
    _sensor_value = 0.0;
}


UtilityAISensors::~UtilityAISensors() {
}

// Handling functions.

double UtilityAISensors::evaluate_sensor_value() {
    return 0.0;
}

// Getters and Setters.

void UtilityAISensors::set_sensor_value( double sensor_value) {
    _sensor_value = sensor_value;
}

double UtilityAISensors::get_sensor_value() const {
    return _sensor_value;
}


/**


// Godot virtuals.
/**
void UtilityAISensors::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAISensors::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAISensors error, no child nodes (states) have been added to the UtilityAISensors '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAISensorsState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAISensors error, the first child is not a UtilityAISensorsState node.");
    _current_state->_enter_state();
}

void UtilityAISensors::_process(double delta ) {
    //if( _update_method != UtilityAISensors_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_Sensors(delta);
}

void UtilityAISensors::_physics_process(double delta ) {
    //if( _update_method != UtilityAISensors_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_Sensors(delta);
}

/**/
