#include "distance_to_vector3.h"
#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

UtilityAIDistanceToVector3SearchCriterion::UtilityAIDistanceToVector3SearchCriterion() {
	_min_distance = 0.0f;
	_max_distance = 100.0f;
	_min_distance_squared = 0.0f;
	_max_distance_squared = _max_distance * _max_distance;
	_span_length = _max_distance_squared - _min_distance_squared;
	_one_over_span_length = 1.0f / _span_length;
	_distance_to_vector = Vector3(0.0, 0.0, 0.0);
}

UtilityAIDistanceToVector3SearchCriterion::~UtilityAIDistanceToVector3SearchCriterion() {
}

void UtilityAIDistanceToVector3SearchCriterion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_distance_to_vector", "distance_to_vector"), &UtilityAIDistanceToVector3SearchCriterion::set_distance_to_vector);
	ClassDB::bind_method(D_METHOD("get_distance_to_vector"), &UtilityAIDistanceToVector3SearchCriterion::get_distance_to_vector);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "distance_to_vector", PROPERTY_HINT_NONE), "set_distance_to_vector", "get_distance_to_vector");

	ClassDB::bind_method(D_METHOD("set_min_distance", "min_distance"), &UtilityAIDistanceToVector3SearchCriterion::set_min_distance);
	ClassDB::bind_method(D_METHOD("get_min_distance"), &UtilityAIDistanceToVector3SearchCriterion::get_min_distance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_distance", PROPERTY_HINT_NONE), "set_min_distance", "get_min_distance");

	ClassDB::bind_method(D_METHOD("set_max_distance", "max_distance"), &UtilityAIDistanceToVector3SearchCriterion::set_max_distance);
	ClassDB::bind_method(D_METHOD("get_max_distance"), &UtilityAIDistanceToVector3SearchCriterion::get_max_distance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_distance", PROPERTY_HINT_NONE), "set_max_distance", "get_max_distance");
}

void UtilityAIDistanceToVector3SearchCriterion::_initialize_criterion() {
}

// Getters and setters.

void UtilityAIDistanceToVector3SearchCriterion::set_distance_to_vector(Vector3 distance_to_vector) {
	_distance_to_vector = distance_to_vector;
}

Vector3 UtilityAIDistanceToVector3SearchCriterion::get_distance_to_vector() const {
	return _distance_to_vector;
}

void UtilityAIDistanceToVector3SearchCriterion::set_min_distance(float min_distance) {
	if (_min_distance < 0.0f)
		return;
	if (_min_distance >= _max_distance)
		return;

	_min_distance = min_distance;
	_min_distance_squared = _min_distance * _min_distance;

	_span_length = _max_distance_squared - _min_distance_squared;
	_one_over_span_length = 1.0f / _span_length;
}

float UtilityAIDistanceToVector3SearchCriterion::get_min_distance() const {
	return _min_distance;
}

void UtilityAIDistanceToVector3SearchCriterion::set_max_distance(float max_distance) {
	if (max_distance <= _min_distance)
		return;
	_max_distance = max_distance;
	_max_distance_squared = _max_distance * _max_distance;

	_span_length = _max_distance_squared - _min_distance_squared;
	_one_over_span_length = 1.0f / _span_length;
}

float UtilityAIDistanceToVector3SearchCriterion::get_max_distance() const {
	return _max_distance;
}

// Handing methods.

void UtilityAIDistanceToVector3SearchCriterion::apply_criterion(Node *node, bool &filter_out, float &score) {
	Node3D *node3d = godot::Object::cast_to<Node3D>(node);
	if (node3d == nullptr)
		return;

	_is_filtered = false;
	_score = 1.0f;

	Vector3 from_to = node3d->get_global_position() - _distance_to_vector;
	float distance_squared = from_to.length_squared();

	if (get_use_for_filtering()) {
		_is_filtered = (distance_squared < _min_distance_squared || distance_squared > _max_distance_squared);
	} //endif do filtering

	if (get_use_for_scoring()) {
		if (distance_squared >= _max_distance_squared) {
			_score = 1.0f;
		} else if (distance_squared <= _min_distance_squared) {
			_score = 0.0f;
		} else {
			float distance_from_lower_limit = distance_squared - _min_distance_squared;
			_score = distance_from_lower_limit * _one_over_span_length;
		}
		if (get_activation_curve().is_valid()) {
			_score = sample_activation_curve(_score);
		}
	} //endif do scoring

	filter_out = _is_filtered;
	score = _score;
}