#include "boolean.h"

#include <godot_cpp/core/class_db.hpp>


using namespace godot;

// Method binds.

void UtilityAIBooleanSensor::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_boolean_value", "boolean_value"), &UtilityAIBooleanSensor::set_boolean_value);
    ClassDB::bind_method(D_METHOD("get_boolean_value"), &UtilityAIBooleanSensor::get_boolean_value);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "boolean_value", PROPERTY_HINT_NONE), "set_boolean_value","get_boolean_value");    
}


// Constructor and destructor.

UtilityAIBooleanSensor::UtilityAIBooleanSensor() {
    _boolean_value = false;
}


UtilityAIBooleanSensor::~UtilityAIBooleanSensor() {
}

// Handling functions.

double UtilityAIBooleanSensor::evaluate_sensor_value() {
    // Here the absolute and relative are the same, so no calculation needed.
    set_sensor_value((double)_boolean_value);
    return get_sensor_value();
}

// Getters and Setters.

void UtilityAIBooleanSensor::set_boolean_value( bool boolean_value ) {
    _boolean_value = boolean_value;
}

bool UtilityAIBooleanSensor::get_boolean_value() const {
    return _boolean_value;
}

