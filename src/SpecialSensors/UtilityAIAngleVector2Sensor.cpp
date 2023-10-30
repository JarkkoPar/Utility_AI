#include "UtilityAIAngleVector2Sensor.h"

#include <godot_cpp/core/class_db.hpp>


using namespace godot;


// Method binds.

void UtilityAIAngleVector2Sensor::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_from_vector", "to_vector"), &UtilityAIAngleVector2Sensor::set_from_vector2);
    ClassDB::bind_method(D_METHOD("get_from_vector"), &UtilityAIAngleVector2Sensor::get_from_vector2);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "from_vector", PROPERTY_HINT_NONE), "set_from_vector","get_from_vector");

    ClassDB::bind_method(D_METHOD("set_to_vector", "to_vector"), &UtilityAIAngleVector2Sensor::set_to_vector2);
    ClassDB::bind_method(D_METHOD("get_to_vector"), &UtilityAIAngleVector2Sensor::get_to_vector2);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "to_vector", PROPERTY_HINT_NONE), "set_to_vector","get_to_vector");

    ClassDB::bind_method(D_METHOD("set_min_angle_euler", "max_angle_euler"), &UtilityAIAngleVector2Sensor::set_min_angle_euler);
    ClassDB::bind_method(D_METHOD("get_min_angle_euler"), &UtilityAIAngleVector2Sensor::get_min_angle_euler);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_angle_euler", PROPERTY_HINT_RANGE, "-180.0,0.0"), "set_min_angle_euler","get_min_angle_euler");

    ClassDB::bind_method(D_METHOD("set_min_angle_radian", "min_angle_radian"), &UtilityAIAngleVector2Sensor::set_min_angle_radian);
    ClassDB::bind_method(D_METHOD("get_min_angle_radian"), &UtilityAIAngleVector2Sensor::get_min_angle_radian);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_angle_radian", PROPERTY_HINT_RANGE, "-3.14159264,0.0"), "set_min_angle_radian","get_min_angle_radian");

    ClassDB::bind_method(D_METHOD("set_max_angle_euler", "max_angle_euler"), &UtilityAIAngleVector2Sensor::set_max_angle_euler);
    ClassDB::bind_method(D_METHOD("get_max_angle_euler"), &UtilityAIAngleVector2Sensor::get_max_angle_euler);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_euler", PROPERTY_HINT_RANGE, "0.0,180.0"), "set_max_angle_euler","get_max_angle_euler");

    ClassDB::bind_method(D_METHOD("set_max_angle_radian", "max_angle_radian"), &UtilityAIAngleVector2Sensor::set_max_angle_radian);
    ClassDB::bind_method(D_METHOD("get_max_angle_radian"), &UtilityAIAngleVector2Sensor::get_max_angle_radian);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_radian", PROPERTY_HINT_RANGE, "0.0,3.14159264"), "set_max_angle_radian","get_max_angle_radian");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_angle_radian", "angle_radian"), &UtilityAIAngleVector2Sensor::set_angle_radian);
    ClassDB::bind_method(D_METHOD("get_angle_radian"), &UtilityAIAngleVector2Sensor::get_angle_radian);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angle_radian", PROPERTY_HINT_NONE ), "set_angle_radian","get_angle_radian");

    ClassDB::bind_method(D_METHOD("set_angle_euler", "angle_euler"), &UtilityAIAngleVector2Sensor::set_angle_euler);
    ClassDB::bind_method(D_METHOD("get_angle_euler"), &UtilityAIAngleVector2Sensor::get_angle_euler);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angle_euler", PROPERTY_HINT_RANGE, "-180.0,180.0"), "set_angle_euler","get_angle_euler");

}


// Constructor and destructor.

UtilityAIAngleVector2Sensor::UtilityAIAngleVector2Sensor() {
    _angle_radian = 0.0;
    _angle_euler = 0.0;
    _min_angle_radian = -Math_PI;
    _min_angle_euler = godot::Math::rad_to_deg(_min_angle_radian);
    _max_angle_radian = Math_PI;
    _max_angle_euler = godot::Math::rad_to_deg(_max_angle_radian);
    _one_over_2_pi = 1.0 / (2.0 * Math_PI);
}


UtilityAIAngleVector2Sensor::~UtilityAIAngleVector2Sensor() {
}

// Handling functions.

double UtilityAIAngleVector2Sensor::evaluate_sensor_value() {
    _angle_radian = _from_vector.angle_to(_to_vector);
    if( _angle_radian < _min_angle_radian ) {
        _angle_radian = _min_angle_radian;
    }else if( _angle_radian > _max_angle_radian ) {
        _angle_radian = _max_angle_radian;
    }
    _angle_euler = godot::Math::rad_to_deg(_angle_radian);
    /**
    if( get_use_absolute_value() ) {
        set_sensor_value(_angle_radian + Math_PI);
    } else {
    /**/
    set_sensor_value((_angle_radian + Math_PI) * _one_over_2_pi );
    /*}*/
    
    return get_sensor_value();
}

// Getters and Setters.

// Configuration values. 

void UtilityAIAngleVector2Sensor::set_to_vector2( Vector2 to ) {
    _to_vector = to;
}

Vector2 UtilityAIAngleVector2Sensor::get_to_vector2() const {
    return _to_vector;
}

void UtilityAIAngleVector2Sensor::set_from_vector2( Vector2 from ) {
    _from_vector = from;
}

Vector2 UtilityAIAngleVector2Sensor::get_from_vector2() const {
    return _from_vector;
}

void UtilityAIAngleVector2Sensor::set_min_angle_radian( double min_angle_radian ) {
    _min_angle_radian = min_angle_radian;
    _min_angle_euler = godot::Math::rad_to_deg(_min_angle_radian);
}

double UtilityAIAngleVector2Sensor::get_min_angle_radian() const {
    return _min_angle_radian;
}

void UtilityAIAngleVector2Sensor::set_min_angle_euler( double min_angle_euler ) {
    _min_angle_euler = min_angle_euler;
    _min_angle_radian = godot::Math::deg_to_rad(_min_angle_euler);
}

double UtilityAIAngleVector2Sensor::get_min_angle_euler() const {
    return _min_angle_euler;
}


void UtilityAIAngleVector2Sensor::set_max_angle_radian( double max_angle_radian ) {
    _max_angle_radian = max_angle_radian;
    _max_angle_euler = godot::Math::rad_to_deg(_max_angle_radian);
}

double UtilityAIAngleVector2Sensor::get_max_angle_radian() const {
    return _max_angle_radian;
}

void UtilityAIAngleVector2Sensor::set_max_angle_euler( double max_angle_euler ) {
    _max_angle_euler = max_angle_euler;
    _max_angle_radian = godot::Math::deg_to_rad(_max_angle_euler);
}

double UtilityAIAngleVector2Sensor::get_max_angle_euler() const {
    return _max_angle_euler;
}

// Debugging / current values.


void UtilityAIAngleVector2Sensor::set_angle_radian( double angle_radian ) {
    _angle_radian = angle_radian;
    _angle_euler = godot::Math::rad_to_deg(angle_radian);
}

double UtilityAIAngleVector2Sensor::get_angle_radian() const {
    return _angle_radian;
}

void UtilityAIAngleVector2Sensor::set_angle_euler( double angle_euler ) {
    _angle_euler = angle_euler;
    _angle_radian = godot::Math::deg_to_rad(_angle_euler);
}

double UtilityAIAngleVector2Sensor::get_angle_euler() const {
    return _angle_euler;
}

