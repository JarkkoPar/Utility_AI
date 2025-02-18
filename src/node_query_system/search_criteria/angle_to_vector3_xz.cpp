#include "angle_to_vector3_xz.h"
#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

UtilityAIAngleToVector3XZSearchCriterion::UtilityAIAngleToVector3XZSearchCriterion() {
	_min_angle_degrees = -90.0;
	_max_angle_degrees = 90.0;
	_min_angle_radians = godot::Math::deg_to_rad(_min_angle_degrees);
	_max_angle_radians = godot::Math::deg_to_rad(_max_angle_degrees);
	_angle_to_direction_vector = Vector3(0.0, 0.0, -1.0);
	_xz_angle_vector = Vector2(1.0, 0.0);
}

UtilityAIAngleToVector3XZSearchCriterion::~UtilityAIAngleToVector3XZSearchCriterion() {
}

void UtilityAIAngleToVector3XZSearchCriterion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_angle_to_direction_vector", "angle_to_direction_vector"), &UtilityAIAngleToVector3XZSearchCriterion::set_angle_to_direction_vector);
	ClassDB::bind_method(D_METHOD("get_angle_to_direction_vector"), &UtilityAIAngleToVector3XZSearchCriterion::get_angle_to_direction_vector);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "angle_to_direction_vector", PROPERTY_HINT_NONE), "set_angle_to_direction_vector", "get_angle_to_direction_vector");

	ClassDB::bind_method(D_METHOD("set_min_angle_degrees", "min_angle_degrees"), &UtilityAIAngleToVector3XZSearchCriterion::set_min_angle_degrees);
	ClassDB::bind_method(D_METHOD("get_min_angle_degrees"), &UtilityAIAngleToVector3XZSearchCriterion::get_min_angle_degrees);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_angle_degrees", PROPERTY_HINT_RANGE, "-180.0,180.0"), "set_min_angle_degrees", "get_min_angle_degrees");

	ClassDB::bind_method(D_METHOD("set_max_angle_degrees", "max_angle_degrees"), &UtilityAIAngleToVector3XZSearchCriterion::set_max_angle_degrees);
	ClassDB::bind_method(D_METHOD("get_max_angle_degrees"), &UtilityAIAngleToVector3XZSearchCriterion::get_max_angle_degrees);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_degrees", PROPERTY_HINT_RANGE, "-180.0,180.0"), "set_max_angle_degrees", "get_max_angle_degrees");
}

void UtilityAIAngleToVector3XZSearchCriterion::_initialize_criterion() {
	if (_max_angle_degrees <= _min_angle_degrees) {
		_max_angle_degrees = _min_angle_degrees + 1.0f;
		if (_max_angle_degrees > 180.0f) {
			_max_angle_degrees = 180.0f;
			_min_angle_degrees = 179.0f;
		}
	}
	_max_angle_radians = godot::Math::deg_to_rad(_max_angle_degrees);
	_min_angle_radians = godot::Math::deg_to_rad(_min_angle_degrees);
	_span_radians = _max_angle_radians - _min_angle_radians;
	_one_over_span_radians = 1.0f / _span_radians;
}

// Getters and setters.

void UtilityAIAngleToVector3XZSearchCriterion::set_angle_to_direction_vector(Vector3 angle_to_direction_vector) {
	_angle_to_direction_vector = angle_to_direction_vector;
	_xz_angle_vector = Vector2(-_angle_to_direction_vector.z, _angle_to_direction_vector.x);
}

Vector3 UtilityAIAngleToVector3XZSearchCriterion::get_angle_to_direction_vector() const {
	return _angle_to_direction_vector;
}

void UtilityAIAngleToVector3XZSearchCriterion::set_min_angle_degrees(float min_angle_degrees) {
	//if( _min_angle_degrees >= _max_angle_degrees ) return;
	if (_min_angle_degrees < -180.0f)
		return;

	_min_angle_degrees = min_angle_degrees;
	_min_angle_radians = godot::Math::deg_to_rad(_min_angle_degrees);
	_span_radians = _max_angle_radians - _min_angle_radians;
	_one_over_span_radians = 1.0f / _span_radians;
}

float UtilityAIAngleToVector3XZSearchCriterion::get_min_angle_degrees() const {
	return _min_angle_degrees;
}

void UtilityAIAngleToVector3XZSearchCriterion::set_max_angle_degrees(float max_angle_degrees) {
	//if( max_angle_degrees <= _min_angle_degrees ) return;
	if (max_angle_degrees > 180.0f)
		return;
	_max_angle_degrees = max_angle_degrees;
	_max_angle_radians = godot::Math::deg_to_rad(_max_angle_degrees);
	_span_radians = _max_angle_radians - _min_angle_radians;
	_one_over_span_radians = 1.0f / _span_radians;
}

float UtilityAIAngleToVector3XZSearchCriterion::get_max_angle_degrees() const {
	return _max_angle_degrees;
}

// Handing methods.

void UtilityAIAngleToVector3XZSearchCriterion::apply_criterion(Node *node, bool &filter_out, float &score) {
	Node3D *node3d = godot::Object::cast_to<Node3D>(node);
	if (node3d == nullptr)
		return;

	_is_filtered = false;
	_score = 1.0f;

	Vector3 node3d_direction_vector = -node3d->get_global_transform().basis.get_column(2);
	Vector2 node3d_2d_direction_vector = Vector2(node3d_direction_vector.z, node3d_direction_vector.x);

	float angle = _xz_angle_vector.angle_to(node3d_2d_direction_vector);

	if (get_use_for_filtering()) {
		_is_filtered = (angle < _min_angle_radians || angle > _max_angle_radians);
	} //endif do filtering

	if (get_use_for_scoring()) {
		if (angle >= _max_angle_radians) {
			_score = 1.0f;
		} else if (angle <= _min_angle_radians) {
			_score = 0.0f;
		} else {
			float angle_from_lower_limit = angle - _min_angle_radians;
			_score = angle_from_lower_limit * _one_over_span_radians;
		}
		if (get_activation_curve().is_valid()) {
			_score = sample_activation_curve(_score);
		}
	} //endif do scoring

	filter_out = _is_filtered;
	score = _score;
}