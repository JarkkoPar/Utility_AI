#include "angle_vector2.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// Method binds.

void UtilityAIAngleVector2Sensor::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_from_vector", "to_vector"), &UtilityAIAngleVector2Sensor::set_from_vector2);
	ClassDB::bind_method(D_METHOD("get_from_vector"), &UtilityAIAngleVector2Sensor::get_from_vector2);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "from_vector", PROPERTY_HINT_NONE), "set_from_vector", "get_from_vector");

	ClassDB::bind_method(D_METHOD("set_to_vector", "to_vector"), &UtilityAIAngleVector2Sensor::set_to_vector2);
	ClassDB::bind_method(D_METHOD("get_to_vector"), &UtilityAIAngleVector2Sensor::get_to_vector2);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "to_vector", PROPERTY_HINT_NONE), "set_to_vector", "get_to_vector");

	ClassDB::bind_method(D_METHOD("set_min_angle_degrees", "max_angle_degrees"), &UtilityAIAngleVector2Sensor::set_min_angle_degrees);
	ClassDB::bind_method(D_METHOD("get_min_angle_degrees"), &UtilityAIAngleVector2Sensor::get_min_angle_degrees);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_angle_degrees", PROPERTY_HINT_RANGE, "-180.0,0.0"), "set_min_angle_degrees", "get_min_angle_degrees");

	ClassDB::bind_method(D_METHOD("set_min_angle_radian", "min_angle_radian"), &UtilityAIAngleVector2Sensor::set_min_angle_radian);
	ClassDB::bind_method(D_METHOD("get_min_angle_radian"), &UtilityAIAngleVector2Sensor::get_min_angle_radian);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_angle_radian", PROPERTY_HINT_RANGE, "-3.14159264,0.0"), "set_min_angle_radian", "get_min_angle_radian");

	ClassDB::bind_method(D_METHOD("set_max_angle_degrees", "max_angle_degrees"), &UtilityAIAngleVector2Sensor::set_max_angle_degrees);
	ClassDB::bind_method(D_METHOD("get_max_angle_degrees"), &UtilityAIAngleVector2Sensor::get_max_angle_degrees);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_degrees", PROPERTY_HINT_RANGE, "0.0,180.0"), "set_max_angle_degrees", "get_max_angle_degrees");

	ClassDB::bind_method(D_METHOD("set_max_angle_radian", "max_angle_radian"), &UtilityAIAngleVector2Sensor::set_max_angle_radian);
	ClassDB::bind_method(D_METHOD("get_max_angle_radian"), &UtilityAIAngleVector2Sensor::get_max_angle_radian);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_radian", PROPERTY_HINT_RANGE, "0.0,3.14159264"), "set_max_angle_radian", "get_max_angle_radian");

	ADD_SUBGROUP("Debugging", "");

	ClassDB::bind_method(D_METHOD("set_angle_radian", "angle_radian"), &UtilityAIAngleVector2Sensor::set_angle_radian);
	ClassDB::bind_method(D_METHOD("get_angle_radian"), &UtilityAIAngleVector2Sensor::get_angle_radian);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angle_radian", PROPERTY_HINT_NONE), "set_angle_radian", "get_angle_radian");

	ClassDB::bind_method(D_METHOD("set_angle_degrees", "angle_degrees"), &UtilityAIAngleVector2Sensor::set_angle_degrees);
	ClassDB::bind_method(D_METHOD("get_angle_degrees"), &UtilityAIAngleVector2Sensor::get_angle_degrees);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angle_degrees", PROPERTY_HINT_RANGE, "-180.0,180.0"), "set_angle_degrees", "get_angle_degrees");
}

// Constructor and destructor.

UtilityAIAngleVector2Sensor::UtilityAIAngleVector2Sensor() {
	_angle_radian = 0.0f;
	_angle_degrees = 0.0f;
	_min_angle_radian = -Math_PI;
	_min_angle_degrees = godot::Math::rad_to_deg(_min_angle_radian);
	_max_angle_radian = Math_PI;
	_max_angle_degrees = godot::Math::rad_to_deg(_max_angle_radian);
	_one_over_2_pi = 1.0f / (2.0f * Math_PI);
}

UtilityAIAngleVector2Sensor::~UtilityAIAngleVector2Sensor() {
}

// Handling functions.

float UtilityAIAngleVector2Sensor::evaluate_sensor_value() {
	_angle_radian = _from_vector.angle_to(_to_vector);
	if (_angle_radian < _min_angle_radian) {
		_angle_radian = _min_angle_radian;
	} else if (_angle_radian > _max_angle_radian) {
		_angle_radian = _max_angle_radian;
	}
	_angle_degrees = godot::Math::rad_to_deg(_angle_radian);
	/**
	if( get_use_absolute_value() ) {
		set_sensor_value(_angle_radian + Math_PI);
	} else {
	/**/
	set_sensor_value((_angle_radian + Math_PI) * _one_over_2_pi);
	/*}*/

	return get_sensor_value();
}

// Getters and Setters.

// Configuration values.

void UtilityAIAngleVector2Sensor::set_to_vector2(Vector2 to) {
	_to_vector = to;
}

Vector2 UtilityAIAngleVector2Sensor::get_to_vector2() const {
	return _to_vector;
}

void UtilityAIAngleVector2Sensor::set_from_vector2(Vector2 from) {
	_from_vector = from;
}

Vector2 UtilityAIAngleVector2Sensor::get_from_vector2() const {
	return _from_vector;
}

void UtilityAIAngleVector2Sensor::set_min_angle_radian(float min_angle_radian) {
	_min_angle_radian = min_angle_radian;
	_min_angle_degrees = godot::Math::rad_to_deg(_min_angle_radian);
}

float UtilityAIAngleVector2Sensor::get_min_angle_radian() const {
	return _min_angle_radian;
}

void UtilityAIAngleVector2Sensor::set_min_angle_degrees(float min_angle_degrees) {
	_min_angle_degrees = min_angle_degrees;
	_min_angle_radian = godot::Math::deg_to_rad(_min_angle_degrees);
}

float UtilityAIAngleVector2Sensor::get_min_angle_degrees() const {
	return _min_angle_degrees;
}

void UtilityAIAngleVector2Sensor::set_max_angle_radian(float max_angle_radian) {
	_max_angle_radian = max_angle_radian;
	_max_angle_degrees = godot::Math::rad_to_deg(_max_angle_radian);
}

float UtilityAIAngleVector2Sensor::get_max_angle_radian() const {
	return _max_angle_radian;
}

void UtilityAIAngleVector2Sensor::set_max_angle_degrees(float max_angle_degrees) {
	_max_angle_degrees = max_angle_degrees;
	_max_angle_radian = godot::Math::deg_to_rad(_max_angle_degrees);
}

float UtilityAIAngleVector2Sensor::get_max_angle_degrees() const {
	return _max_angle_degrees;
}

// Debugging / current values.

void UtilityAIAngleVector2Sensor::set_angle_radian(float angle_radian) {
	_angle_radian = angle_radian;
	_angle_degrees = godot::Math::rad_to_deg(angle_radian);
}

float UtilityAIAngleVector2Sensor::get_angle_radian() const {
	return _angle_radian;
}

void UtilityAIAngleVector2Sensor::set_angle_degrees(float angle_degrees) {
	_angle_degrees = angle_degrees;
	_angle_radian = godot::Math::deg_to_rad(_angle_degrees);
}

float UtilityAIAngleVector2Sensor::get_angle_degrees() const {
	return _angle_degrees;
}
