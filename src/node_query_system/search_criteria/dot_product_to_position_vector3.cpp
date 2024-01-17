#include "dot_product_to_position_vector3.h"
#include <godot_cpp/classes/node3d.hpp>

using namespace godot;


UtilityAIDotProductToPositionVector3SearchCriterion::UtilityAIDotProductToPositionVector3SearchCriterion() {
    _filtering_value = 0.0f;
    _filtering_rule = UtilityAIDotProductToPositionVector3SearchCriteriaFilteringRule::LessOrEqual;
    
    _dot_product_position_vector = Vector3(0.0, 0.0, -1.0);
}


UtilityAIDotProductToPositionVector3SearchCriterion::~UtilityAIDotProductToPositionVector3SearchCriterion() {
    
}


void UtilityAIDotProductToPositionVector3SearchCriterion::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_dot_product_position_vector", "dot_product_position_vector"), &UtilityAIDotProductToPositionVector3SearchCriterion::set_dot_product_position_vector);
    ClassDB::bind_method(D_METHOD("get_dot_product_position_vector"), &UtilityAIDotProductToPositionVector3SearchCriterion::get_dot_product_position_vector);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "dot_product_position", PROPERTY_HINT_NONE), "set_dot_product_position_vector","get_dot_product_position_vector");
    
    
    ClassDB::bind_method(D_METHOD("set_filtering_value", "filtering_value"), &UtilityAIDotProductToPositionVector3SearchCriterion::set_filtering_value);
    ClassDB::bind_method(D_METHOD("get_filtering_value"), &UtilityAIDotProductToPositionVector3SearchCriterion::get_filtering_value);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "filtering_value", PROPERTY_HINT_RANGE, "-1.0,1.0"), "set_filtering_value","get_filtering_value");
    
    ClassDB::bind_method(D_METHOD("set_filtering_rule", "filtering_rule"), &UtilityAIDotProductToPositionVector3SearchCriterion::set_filtering_rule);
    ClassDB::bind_method(D_METHOD("get_filtering_rule"), &UtilityAIDotProductToPositionVector3SearchCriterion::get_filtering_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "filtering_rule", PROPERTY_HINT_ENUM, "LessThan:0,LessOrEqual:1,Equal:2,MoreOrEqual:3,MoreThan:4"), "set_filtering_rule","get_filtering_rule");
    
}


void UtilityAIDotProductToPositionVector3SearchCriterion::_initialize_criterion() {
    
}


// Getters and setters.

void UtilityAIDotProductToPositionVector3SearchCriterion::set_dot_product_position_vector( Vector3 dot_product_position_vector ) {
    _dot_product_position_vector = dot_product_position_vector;
}


Vector3 UtilityAIDotProductToPositionVector3SearchCriterion::get_dot_product_position_vector() const {
    return _dot_product_position_vector;
}


void UtilityAIDotProductToPositionVector3SearchCriterion::set_filtering_value( float filtering_value ) {
    _filtering_value = filtering_value;
}


float UtilityAIDotProductToPositionVector3SearchCriterion::get_filtering_value() const {
    return _filtering_value;
}


void UtilityAIDotProductToPositionVector3SearchCriterion::set_filtering_rule( int filtering_rule ) {
    _filtering_rule = filtering_rule;
}


int UtilityAIDotProductToPositionVector3SearchCriterion::get_filtering_rule() const {
    return _filtering_rule;
}

// Handing methods.

void UtilityAIDotProductToPositionVector3SearchCriterion::apply_criterion( Node* node, bool& filter_out, float& score ) {
    Node3D* node3d = godot::Object::cast_to<Node3D>(node);
    if( node3d == nullptr ) return;

    _is_filtered = false;
    _score = 1.0f;

    Vector3 node3d_direction_vector = -node3d->get_global_transform().basis.get_column(2);
    Vector3 node3d_position_vector = node3d->get_global_position();
    Vector3 node3d_from_to_position_vector = (_dot_product_position_vector - node3d_position_vector).normalized();

    float DotProductToPosition = node3d_direction_vector.dot(node3d_from_to_position_vector);
    
    if( get_use_for_filtering() ) {
        switch(_filtering_rule) {
            case UtilityAIDotProductToPositionVector3SearchCriteriaFilteringRule::LessThan:
            {
                _is_filtered = (DotProductToPosition < _filtering_value);
            }
            break;
            case UtilityAIDotProductToPositionVector3SearchCriteriaFilteringRule::LessOrEqual:
            {
                _is_filtered = (DotProductToPosition <= _filtering_value);
            }
            break;
            case UtilityAIDotProductToPositionVector3SearchCriteriaFilteringRule::Equal:
            {
                _is_filtered = (DotProductToPosition == _filtering_value);
            }
            break;
            case UtilityAIDotProductToPositionVector3SearchCriteriaFilteringRule::MoreOrEqual:
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
        _score = DotProductToPosition * 0.5f + 0.5f;
        if( get_activation_curve().is_valid()) {
            _score = sample_activation_curve(_score);
        }
    }//endif do scoring
    
    filter_out = _is_filtered;
    score = _score;
    
}