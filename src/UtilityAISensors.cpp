#include "UtilityAISensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

// Method binds.

void UtilityAISensors::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_sensor_value", "sensor_value"), &UtilityAISensors::set_sensor_value);
    ClassDB::bind_method(D_METHOD("get_sensor_value"), &UtilityAISensors::get_sensor_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sensor_value", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_sensor_value","get_sensor_value");
    
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

