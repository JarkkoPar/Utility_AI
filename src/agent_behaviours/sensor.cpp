#include "sensor.h"

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

float UtilityAISensor::evaluate_sensor_value() {
    _has_sensor_value_changed = false;
    return get_sensor_value();
}

// Getters and Setters.


// Godot virtuals.
