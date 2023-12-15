#include "dot_product_to_position_vector2.h"
#include <godot_cpp/classes/node2d.hpp>

using namespace godot;


UtilityAIDotProductToPositionVector2SearchCriterion::UtilityAIDotProductToPositionVector2SearchCriterion() {
    _filtering_value = 0.0;
    _filtering_rule = UtilityAIDotProductToPositionVector2SearchCriteriaFilteringRule::LessOrEqual;
    
    _dot_product_position_vector = Vector2(1.0, 0.0);
}


UtilityAIDotProductToPositionVector2SearchCriterion::~UtilityAIDotProductToPositionVector2SearchCriterion() {
    
}


void UtilityAIDotProductToPositionVector2SearchCriterion::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_dot_product_position_vector", "dot_product_position_vector"), &UtilityAIDotProductToPositionVector2SearchCriterion::set_dot_product_position_vector);
    ClassDB::bind_method(D_METHOD("get_dot_product_position_vector"), &UtilityAIDotProductToPositionVector2SearchCriterion::get_dot_product_position_vector);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "dot_product_position", PROPERTY_HINT_NONE), "set_dot_product_position_vector","get_dot_product_position_vector");
    
    
    ClassDB::bind_method(D_METHOD("set_filtering_value", "filtering_value"), &UtilityAIDotProductToPositionVector2SearchCriterion::set_filtering_value);
    ClassDB::bind_method(D_METHOD("get_filtering_value"), &UtilityAIDotProductToPositionVector2SearchCriterion::get_filtering_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "filtering_value", PROPERTY_HINT_RANGE, "-1.0,1.0"), "set_filtering_value","get_filtering_value");
    
    ClassDB::bind_method(D_METHOD("set_filtering_rule", "filtering_rule"), &UtilityAIDotProductToPositionVector2SearchCriterion::set_filtering_rule);
    ClassDB::bind_method(D_METHOD("get_filtering_rule"), &UtilityAIDotProductToPositionVector2SearchCriterion::get_filtering_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "filtering_rule", PROPERTY_HINT_ENUM, "LessThan:0,LessOrEqual:1,Equal:2,MoreOrEqual:3,MoreThan:4"), "set_filtering_rule","get_filtering_rule");
    
}


void UtilityAIDotProductToPositionVector2SearchCriterion::_initialize_criterion() {
    
}


// Getters and setters.

void UtilityAIDotProductToPositionVector2SearchCriterion::set_dot_product_position_vector( Vector2 dot_product_position_vector ) {
    _dot_product_position_vector = dot_product_position_vector;
}


Vector2 UtilityAIDotProductToPositionVector2SearchCriterion::get_dot_product_position_vector() const {
    return _dot_product_position_vector;
}


void UtilityAIDotProductToPositionVector2SearchCriterion::set_filtering_value( double filtering_value ) {
    _filtering_value = filtering_value;
}


double UtilityAIDotProductToPositionVector2SearchCriterion::get_filtering_value() const {
    return _filtering_value;
}


void UtilityAIDotProductToPositionVector2SearchCriterion::set_filtering_rule( int filtering_rule ) {
    _filtering_rule = filtering_rule;
}


int UtilityAIDotProductToPositionVector2SearchCriterion::get_filtering_rule() const {
    return _filtering_rule;
}

// Handing methods.

void UtilityAIDotProductToPositionVector2SearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    Node2D* node2d = godot::Object::cast_to<Node2D>(node);
    if( node2d == nullptr ) return;

    _is_filtered = false;
    _score = 0.0;

    Vector2 node2d_position_vector = node2d->get_global_position();
    Vector2 node2d_direction_vector = Vector2(1.0,0.0).rotated(node2d->get_global_rotation());

    Vector2 node2d_from_to_vector = (_dot_product_position_vector - node2d_position_vector).normalized();

    double DotProductToPosition = node2d_direction_vector.dot(node2d_from_to_vector);
    
    if( get_use_for_filtering() ) {
        switch(_filtering_rule) {
            case UtilityAIDotProductToPositionVector2SearchCriteriaFilteringRule::LessThan:
            {
                _is_filtered = (DotProductToPosition < _filtering_value);
            }
            break;
            case UtilityAIDotProductToPositionVector2SearchCriteriaFilteringRule::LessOrEqual:
            {
                _is_filtered = (DotProductToPosition <= _filtering_value);
            }
            break;
            case UtilityAIDotProductToPositionVector2SearchCriteriaFilteringRule::Equal:
            {
                _is_filtered = (DotProductToPosition == _filtering_value);
            }
            break;
            case UtilityAIDotProductToPositionVector2SearchCriteriaFilteringRule::MoreOrEqual:
            {
                _is_filtered = (DotProductToPosition >= _filtering_value);
            }
            break;
            default:
            {
                _is_filtered = (DotProductToPosition > _filtering_value);
            }
            break;
        }
    }//endif do filtering

    if( get_use_for_scoring() ) {
        _score = DotProductToPosition * 0.5 + 0.5;
        if( get_activation_curve().is_valid()) {
            _score = sample_activation_curve(_score);
        }
    }//endif do scoring
    
    filter_out = _is_filtered;
    score = _score;
    
}