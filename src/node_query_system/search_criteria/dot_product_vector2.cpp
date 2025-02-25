#include "dot_product_vector2.h"
#include <godot_cpp/classes/node2d.hpp>

using namespace godot;

UtilityAIDotProductVector2SearchCriterion::UtilityAIDotProductVector2SearchCriterion() {
	_filtering_value = 0.0;
	_filtering_rule = UtilityAIDotProductVector2SearchCriteriaFilteringRule::LessOrEqual;

	_dot_product_direction_vector = Vector2(1.0, 0.0);
}

UtilityAIDotProductVector2SearchCriterion::~UtilityAIDotProductVector2SearchCriterion() {
}

void UtilityAIDotProductVector2SearchCriterion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_dot_product_direction_vector", "dot_product_direction_vector"), &UtilityAIDotProductVector2SearchCriterion::set_dot_product_direction_vector);
	ClassDB::bind_method(D_METHOD("get_dot_product_direction_vector"), &UtilityAIDotProductVector2SearchCriterion::get_dot_product_direction_vector);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "dot_product_vector", PROPERTY_HINT_NONE), "set_dot_product_direction_vector", "get_dot_product_direction_vector");

	ClassDB::bind_method(D_METHOD("set_filtering_value", "filtering_value"), &UtilityAIDotProductVector2SearchCriterion::set_filtering_value);
	ClassDB::bind_method(D_METHOD("get_filtering_value"), &UtilityAIDotProductVector2SearchCriterion::get_filtering_value);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "filtering_value", PROPERTY_HINT_RANGE, "-1.0,1.0"), "set_filtering_value", "get_filtering_value");

	ClassDB::bind_method(D_METHOD("set_filtering_rule", "filtering_rule"), &UtilityAIDotProductVector2SearchCriterion::set_filtering_rule);
	ClassDB::bind_method(D_METHOD("get_filtering_rule"), &UtilityAIDotProductVector2SearchCriterion::get_filtering_rule);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "filtering_rule", PROPERTY_HINT_ENUM, "LessThan:0,LessOrEqual:1,Equal:2,MoreOrEqual:3,MoreThan:4"), "set_filtering_rule", "get_filtering_rule");
}

void UtilityAIDotProductVector2SearchCriterion::_initialize_criterion() {
}

// Getters and setters.

void UtilityAIDotProductVector2SearchCriterion::set_dot_product_direction_vector(Vector2 dot_product_direction_vector) {
	_dot_product_direction_vector = dot_product_direction_vector;
}

Vector2 UtilityAIDotProductVector2SearchCriterion::get_dot_product_direction_vector() const {
	return _dot_product_direction_vector;
}

void UtilityAIDotProductVector2SearchCriterion::set_filtering_value(float filtering_value) {
	_filtering_value = filtering_value;
}

float UtilityAIDotProductVector2SearchCriterion::get_filtering_value() const {
	return _filtering_value;
}

void UtilityAIDotProductVector2SearchCriterion::set_filtering_rule(int filtering_rule) {
	_filtering_rule = filtering_rule;
}

int UtilityAIDotProductVector2SearchCriterion::get_filtering_rule() const {
	return _filtering_rule;
}

// Handing methods.

void UtilityAIDotProductVector2SearchCriterion::apply_criterion(Node *node, bool &filter_out, float &score) {
	Node2D *node2d = godot::Object::cast_to<Node2D>(node);
	if (node2d == nullptr)
		return;

	_is_filtered = false;
	_score = 1.0f;

	Vector2 node2d_direction_vector = Vector2(1.0f, 0.0f).rotated(node2d->get_global_rotation());

	float dotproduct = _dot_product_direction_vector.dot(node2d_direction_vector);

	if (get_use_for_filtering()) {
		switch (_filtering_rule) {
			case UtilityAIDotProductVector2SearchCriteriaFilteringRule::LessThan: {
				_is_filtered = (dotproduct < _filtering_value);
			} break;
			case UtilityAIDotProductVector2SearchCriteriaFilteringRule::LessOrEqual: {
				_is_filtered = (dotproduct <= _filtering_value);
			} break;
			case UtilityAIDotProductVector2SearchCriteriaFilteringRule::Equal: {
				_is_filtered = (dotproduct == _filtering_value);
			} break;
			case UtilityAIDotProductVector2SearchCriteriaFilteringRule::MoreOrEqual: {
				_is_filtered = (dotproduct >= _filtering_value);
			} break;
			default: {
				_is_filtered = (dotproduct > _filtering_value);
			} break;
		}
	} //endif do filtering

	if (get_use_for_scoring()) {
		_score = dotproduct * 0.5f + 0.5f;
		if (get_activation_curve().is_valid()) {
			_score = sample_activation_curve(_score);
		}
	} //endif do scoring

	filter_out = _is_filtered;
	score = _score;
}