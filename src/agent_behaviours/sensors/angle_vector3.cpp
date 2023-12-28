#include "angle_vector3.h"

#include <godot_cpp/core/class_db.hpp>


using namespace godot;


// Method binds.

void UtilityAIAngleVector3Sensor::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_from_vector", "to_vector"), &UtilityAIAngleVector3Sensor::set_from_vector3);
    ClassDB::bind_method(D_METHOD("get_from_vector"), &UtilityAIAngleVector3Sensor::get_from_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "from_vector", PROPERTY_HINT_NONE), "set_from_vector","get_from_vector");

    ClassDB::bind_method(D_METHOD("set_to_vector", "to_vector"), &UtilityAIAngleVector3Sensor::set_to_vector3);
    ClassDB::bind_method(D_METHOD("get_to_vector"), &UtilityAIAngleVector3Sensor::get_to_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "to_vector", PROPERTY_HINT_NONE), "set_to_vector","get_to_vector");

    ClassDB::bind_method(D_METHOD("set_max_angle_degrees", "max_angle_degrees"), &UtilityAIAngleVector3Sensor::set_max_angle_degrees);
    ClassDB::bind_method(D_METHOD("get_max_angle_degrees"), &UtilityAIAngleVector3Sensor::get_max_angle_degrees);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_degrees", PROPERTY_HINT_RANGE, "-179.99999999,179.99999999"), "set_max_angle_degrees","get_max_angle_degrees");

    ClassDB::bind_method(D_METHOD("set_max_angle_radian", "max_angle_radian"), &UtilityAIAngleVector3Sensor::set_max_angle_radian);
    ClassDB::bind_method(D_METHOD("get_max_angle_radian"), &UtilityAIAngleVector3Sensor::get_max_angle_radian);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_radian", PROPERTY_HINT_RANGE, "-3.14159264,3.14159264"), "set_max_angle_radian","get_max_angle_radian");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_angle_radian", "angle_radian"), &UtilityAIAngleVector3Sensor::set_angle_radian);
    ClassDB::bind_method(D_METHOD("get_angle_radian"), &UtilityAIAngleVector3Sensor::get_angle_radian);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angle_radian", PROPERTY_HINT_RANGE, "-3.14159264,3.14159264"), "set_angle_radian","get_angle_radian");

    ClassDB::bind_method(D_METHOD("set_angle_degrees", "angle_degrees"), &UtilityAIAngleVector3Sensor::set_angle_degrees);
    ClassDB::bind_method(D_METHOD("get_angle_degrees"), &UtilityAIAngleVector3Sensor::get_angle_degrees);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angle_degrees", PROPERTY_HINT_RANGE, "-179.99999999,179.99999999"), "set_angle_degrees","get_angle_degrees");

}


// Constructor and destructor.

UtilityAIAngleVector3Sensor::UtilityAIAngleVector3Sensor() {
    _angle_radian = 0.0;
    _angle_degrees = 0.0;
    _max_angle_radian = 2.0 * Math_PI;
    _max_angle_degrees = 360.0;
}


UtilityAIAngleVector3Sensor::~UtilityAIAngleVector3Sensor() {
}

// Handling functions.

float UtilityAIAngleVector3Sensor::evaluate_sensor_value() {
    _angle_radian = _from_vector.angle_to(_to_vector);
    _angle_degrees = godot::Math::rad_to_deg(_angle_radian);
    /**
    if( get_use_absolute_value() ) {
        set_sensor_value(_angle_radian);
    } else {
    /**/
    set_sensor_value(_angle_radian * _one_over_max_angle_radian);
    /*}*/
    return get_sensor_value();
}

// Getters and Setters.

// Configuration values. 

void UtilityAIAngleVector3Sensor::set_to_vector3( Vector3 to ) {
    _to_vector = to;
}

Vector3 UtilityAIAngleVector3Sensor::get_to_vector3() const {
    return _to_vector;
}

void UtilityAIAngleVector3Sensor::set_from_vector3( Vector3 from ) {
    _from_vector = from;
}

Vector3 UtilityAIAngleVector3Sensor::get_from_vector3() const {
    return _from_vector;
}

void UtilityAIAngleVector3Sensor::set_max_angle_radian( float max_angle_radian ) {
    if( max_angle_radian == 0.0 ) {
        return;
    }
    _max_angle_radian = max_angle_radian;
    _max_angle_degrees = godot::Math::rad_to_deg(_max_angle_radian);
    _one_over_max_angle_radian = 1.0 / _max_angle_radian;
}

float UtilityAIAngleVector3Sensor::get_max_angle_radian() const {
    return _max_angle_radian;
}

void UtilityAIAngleVector3Sensor::set_max_angle_degrees( float max_angle_degrees ) {
    if( max_angle_degrees == 0.0 ) {
        return;
    }
    _max_angle_degrees = max_angle_degrees;
    _max_angle_radian = godot::Math::deg_to_rad(_max_angle_degrees);
    _one_over_max_angle_radian = 1.0 / _max_angle_radian;
}

float UtilityAIAngleVector3Sensor::get_max_angle_degrees() const {
    return _max_angle_degrees;
}

// Debugging / current values.


void UtilityAIAngleVector3Sensor::set_angle_radian( float angle_radian ) {
    _angle_radian = angle_radian;
    _angle_degrees = godot::Math::rad_to_deg(angle_radian);
}

float UtilityAIAngleVector3Sensor::get_angle_radian() const {
    return _angle_radian;
}

void UtilityAIAngleVector3Sensor::set_angle_degrees( float angle_degrees ) {
    _angle_degrees = angle_degrees;
    _angle_radian = godot::Math::deg_to_rad(_angle_degrees);
}

float UtilityAIAngleVector3Sensor::get_angle_degrees() const {
    return _angle_degrees;
}

