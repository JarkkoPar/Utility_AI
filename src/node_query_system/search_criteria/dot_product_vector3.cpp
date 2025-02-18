#include "dot_product_vector3.h"
#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

UtilityAIDotProductVector3SearchCriterion::UtilityAIDotProductVector3SearchCriterion() {
	_filtering_value = 0.0f;
	_filtering_rule = UtilityAIDotProductVector3SearchCriteriaFilteringRule::LessOrEqual;

	_dot_product_direction_vector = Vector3(0.0, 0.0, -1.0);
}

UtilityAIDotProductVector3SearchCriterion::~UtilityAIDotProductVector3SearchCriterion() {
}

void UtilityAIDotProductVector3SearchCriterion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_dot_product_direction_vector", "dot_product_direction_vector"), &UtilityAIDotProductVector3SearchCriterion::set_dot_product_direction_vector);
	ClassDB::bind_method(D_METHOD("get_dot_product_direction_vector"), &UtilityAIDotProductVector3SearchCriterion::get_dot_product_direction_vector);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "dot_product_vector", PROPERTY_HINT_NONE), "set_dot_product_direction_vector", "get_dot_product_direction_vector");

	ClassDB::bind_method(D_METHOD("set_filtering_value", "filtering_value"), &UtilityAIDotProductVector3SearchCriterion::set_filtering_value);
	ClassDB::bind_method(D_METHOD("get_filtering_value"), &UtilityAIDotProductVector3SearchCriterion::get_filtering_value);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "filtering_value", PROPERTY_HINT_RANGE, "-1.0,1.0"), "set_filtering_value", "get_filtering_value");

	ClassDB::bind_method(D_METHOD("set_filtering_rule", "filtering_rule"), &UtilityAIDotProductVector3SearchCriterion::set_filtering_rule);
	ClassDB::bind_method(D_METHOD("get_filtering_rule"), &UtilityAIDotProductVector3SearchCriterion::get_filtering_rule);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "filtering_rule", PROPERTY_HINT_ENUM, "LessThan:0,LessOrEqual:1,Equal:2,MoreOrEqual:3,MoreThan:4"), "set_filtering_rule", "get_filtering_rule");
}

void UtilityAIDotProductVector3SearchCriterion::_initialize_criterion() {
}

// Getters and setters.

void UtilityAIDotProductVector3SearchCriterion::set_dot_product_direction_vector(Vector3 dot_product_direction_vector) {
	_dot_product_direction_vector = dot_product_direction_vector;
}

Vector3 UtilityAIDotProductVector3SearchCriterion::get_dot_product_direction_vector() const {
	return _dot_product_direction_vector;
}

void UtilityAIDotProductVector3SearchCriterion::set_filtering_value(float filtering_value) {
	_filtering_value = filtering_value;
}

float UtilityAIDotProductVector3SearchCriterion::get_filtering_value() const {
	return _filtering_value;
}

void UtilityAIDotProductVector3SearchCriterion::set_filtering_rule(int filtering_rule) {
	_filtering_rule = filtering_rule;
}

int UtilityAIDotProductVector3SearchCriterion::get_filtering_rule() const {
	return _filtering_rule;
}

// Handing methods.

void UtilityAIDotProductVector3SearchCriterion::apply_criterion(Node *node, bool &filter_out, float &score) {
	Node3D *node3d = godot::Object::cast_to<Node3D>(node);
	if (node3d == nullptr)
		return;

	_is_filtered = false;
	_score = 1.0f;

	Vector3 node3d_direction_vector = -node3d->get_global_transform().basis.get_column(2);

	float dotproduct = _dot_product_direction_vector.dot(node3d_direction_vector);

	if (get_use_for_filtering()) {
		switch (_filtering_rule) {
			case UtilityAIDotProductVector3SearchCriteriaFilteringRule::LessThan: {
				_is_filtered = (dotproduct < _filtering_value);
			} break;
			case UtilityAIDotProductVector3SearchCriteriaFilteringRule::LessOrEqual: {
				_is_filtered = (dotproduct <= _filtering_value);
			} break;
			case UtilityAIDotProductVector3SearchCriteriaFilteringRule::Equal: {
				_is_filtered = (dotproduct == _filtering_value);
			} break;
			case UtilityAIDotProductVector3SearchCriteriaFilteringRule::MoreOrEqual: {
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