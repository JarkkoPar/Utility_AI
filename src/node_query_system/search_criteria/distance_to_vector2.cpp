#include "distance_to_vector2.h"
#include <godot_cpp/classes/node2d.hpp>

using namespace godot;

UtilityAIDistanceToVector2SearchCriterion::UtilityAIDistanceToVector2SearchCriterion() {
	_min_distance = 0.0;
	_max_distance = 100.0;
	_min_distance_squared = 0.0;
	_max_distance_squared = _max_distance * _max_distance;
	_span_length = _max_distance_squared - _min_distance_squared;
	_one_over_span_length = 1.0 / _span_length;
	_distance_to_vector = Vector2(0.0, 0.0);
}

UtilityAIDistanceToVector2SearchCriterion::~UtilityAIDistanceToVector2SearchCriterion() {
}

void UtilityAIDistanceToVector2SearchCriterion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_distance_to_vector", "distance_to_vector"), &UtilityAIDistanceToVector2SearchCriterion::set_distance_to_vector);
	ClassDB::bind_method(D_METHOD("get_distance_to_vector"), &UtilityAIDistanceToVector2SearchCriterion::get_distance_to_vector);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "distance_to_vector", PROPERTY_HINT_NONE), "set_distance_to_vector", "get_distance_to_vector");

	ClassDB::bind_method(D_METHOD("set_min_distance", "min_distance"), &UtilityAIDistanceToVector2SearchCriterion::set_min_distance);
	ClassDB::bind_method(D_METHOD("get_min_distance"), &UtilityAIDistanceToVector2SearchCriterion::get_min_distance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_distance", PROPERTY_HINT_NONE), "set_min_distance", "get_min_distance");

	ClassDB::bind_method(D_METHOD("set_max_distance", "max_distance"), &UtilityAIDistanceToVector2SearchCriterion::set_max_distance);
	ClassDB::bind_method(D_METHOD("get_max_distance"), &UtilityAIDistanceToVector2SearchCriterion::get_max_distance);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_distance", PROPERTY_HINT_NONE), "set_max_distance", "get_max_distance");
}

void UtilityAIDistanceToVector2SearchCriterion::_initialize_criterion() {
}

// Getters and setters.

void UtilityAIDistanceToVector2SearchCriterion::set_distance_to_vector(Vector2 distance_to_vector) {
	_distance_to_vector = distance_to_vector;
}

Vector2 UtilityAIDistanceToVector2SearchCriterion::get_distance_to_vector() const {
	return _distance_to_vector;
}

void UtilityAIDistanceToVector2SearchCriterion::set_min_distance(float min_distance) {
	if (_min_distance < 0.0)
		return;
	if (_min_distance >= _max_distance)
		return;

	_min_distance = min_distance;
	_min_distance_squared = _min_distance * _min_distance;

	_span_length = _max_distance_squared - _min_distance_squared;
	_one_over_span_length = 1.0 / _span_length;
}

float UtilityAIDistanceToVector2SearchCriterion::get_min_distance() const {
	return _min_distance;
}

void UtilityAIDistanceToVector2SearchCriterion::set_max_distance(float max_distance) {
	if (max_distance <= _min_distance)
		return;
	_max_distance = max_distance;
	_max_distance_squared = _max_distance * _max_distance;

	_span_length = _max_distance_squared - _min_distance_squared;
	_one_over_span_length = 1.0 / _span_length;
}

float UtilityAIDistanceToVector2SearchCriterion::get_max_distance() const {
	return _max_distance;
}

// Handing methods.

void UtilityAIDistanceToVector2SearchCriterion::apply_criterion(Node *node, bool &filter_out, float &score) {
	Node2D *node2d = godot::Object::cast_to<Node2D>(node);
	if (node2d == nullptr)
		return;

	_is_filtered = false;
	_score = 1.0f;

	Vector2 from_to = node2d->get_global_position() - _distance_to_vector;
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