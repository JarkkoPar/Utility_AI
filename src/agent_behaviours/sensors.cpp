#include "sensors.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

// Method binds.

void UtilityAISensors::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("set_use_absolute_value", "use_absolute_value"), &UtilityAISensors::set_use_absolute_value);
    //ClassDB::bind_method(D_METHOD("get_use_absolute_value"), &UtilityAISensors::get_use_absolute_value);
    //ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_absolute_value", PROPERTY_HINT_NONE), "set_use_absolute_value","get_use_absolute_value");
    
    ClassDB::bind_method(D_METHOD("set_sensor_value", "sensor_value"), &UtilityAISensors::set_sensor_value);
    ClassDB::bind_method(D_METHOD("get_sensor_value"), &UtilityAISensors::get_sensor_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sensor_value", PROPERTY_HINT_RANGE, "0.0,1.0,or_less,or_greater"), "set_sensor_value","get_sensor_value");
    
}


// Constructor and destructor.

UtilityAISensors::UtilityAISensors() {
    _sensor_value = 0.0;
    //_use_absolute_value = true;
}


UtilityAISensors::~UtilityAISensors() {
}


// Godot virtuals.

void UtilityAISensors::_ready() {
    initialize_sensor();
}


void UtilityAISensors::_exit_tree() {
    uninitialize_sensor();
}

// Handling methods.

void UtilityAISensors::initialize_sensor() {

}

float UtilityAISensors::evaluate_sensor_value() {
    return 0.0;
}

// Getters and Setters.

void UtilityAISensors::set_sensor_value( float sensor_value) {
    _sensor_value = sensor_value;
}

float UtilityAISensors::get_sensor_value() const {
    return _sensor_value;
}

/**
void UtilityAISensors::set_use_absolute_value( bool use_absolute_value ) {
    _use_absolute_value = use_absolute_value;
}

bool UtilityAISensors::get_use_absolute_value() const {
    return _use_absolute_value;
}
/**/
