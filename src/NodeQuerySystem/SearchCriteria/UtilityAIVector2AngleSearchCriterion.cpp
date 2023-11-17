#include "UtilityAIVector2AngleSearchCriterion.h"
#include <godot_cpp/classes/node2d.hpp>

using namespace godot;


UtilityAIVector2AngleSearchCriterion::UtilityAIVector2AngleSearchCriterion() {
    _min_angle_degrees = -90.0;
    _max_angle_degrees =  90.0;
    _angle_to_direction_vector = Vector2(1.0,0.0);
}


UtilityAIVector2AngleSearchCriterion::~UtilityAIVector2AngleSearchCriterion() {

}


void UtilityAIVector2AngleSearchCriterion::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_angle_to_direction_vector", "angle_to_direction_vector"), &UtilityAIVector2AngleSearchCriterion::set_angle_to_direction_vector);
    ClassDB::bind_method(D_METHOD("get_angle_to_direction_vector"), &UtilityAIVector2AngleSearchCriterion::get_angle_to_direction_vector);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "Angle_to_vector", PROPERTY_HINT_NONE), "set_angle_to_direction_vector","get_angle_to_direction_vector");
    
    ClassDB::bind_method(D_METHOD("set_min_angle_degrees", "min_angle_degrees"), &UtilityAIVector2AngleSearchCriterion::set_min_angle_degrees);
    ClassDB::bind_method(D_METHOD("get_min_angle_degrees"), &UtilityAIVector2AngleSearchCriterion::get_min_angle_degrees);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_angle_degrees", PROPERTY_HINT_RANGE, "-180.0,180.0"), "set_min_angle_degrees","get_min_angle_degrees");
    
    ClassDB::bind_method(D_METHOD("set_max_angle_degrees", "max_angle_degrees"), &UtilityAIVector2AngleSearchCriterion::set_max_angle_degrees);
    ClassDB::bind_method(D_METHOD("get_max_angle_degrees"), &UtilityAIVector2AngleSearchCriterion::get_max_angle_degrees);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_degrees", PROPERTY_HINT_RANGE, "-180.0,180.0"), "set_max_angle_degrees","get_max_angle_degrees");
    
    
}


void UtilityAIVector2AngleSearchCriterion::_initialize_criterion() {
    _max_angle_radians = godot::Math::deg_to_rad(_max_angle_degrees);
    _min_angle_radians = godot::Math::deg_to_rad(_min_angle_degrees);
    _span_radians = _max_angle_radians - _min_angle_radians;
    _one_over_span_radians = 1.0 / _span_radians;
}


// Getters and setters.

void UtilityAIVector2AngleSearchCriterion::set_angle_to_direction_vector( Vector2 angle_to_direction_vector ) {
    _angle_to_direction_vector = angle_to_direction_vector;
}


Vector2 UtilityAIVector2AngleSearchCriterion::get_angle_to_direction_vector() const {
    return _angle_to_direction_vector;
}


void UtilityAIVector2AngleSearchCriterion::set_min_angle_degrees( double min_angle_degrees ) {
    //if( _min_angle_degrees >= _max_angle_degrees ) return;
    if( _min_angle_degrees < -180.0 ) return;
    
    _min_angle_degrees = min_angle_degrees;
    _min_angle_radians = godot::Math::deg_to_rad(_min_angle_degrees);
    _span_radians = _max_angle_radians - _min_angle_radians;
    _one_over_span_radians = 1.0 / _span_radians;
}


double UtilityAIVector2AngleSearchCriterion::get_min_angle_degrees() const {
    return _min_angle_degrees;
}


void UtilityAIVector2AngleSearchCriterion::set_max_angle_degrees( double max_angle_degrees ) {
    //if( max_angle_degrees <= _min_angle_degrees ) return;
    if( max_angle_degrees > 180.0 ) return;
    _max_angle_degrees = max_angle_degrees;
    _max_angle_radians = godot::Math::deg_to_rad(_max_angle_degrees);
    _span_radians = _max_angle_radians - _min_angle_radians;
    _one_over_span_radians = 1.0 / _span_radians;
}


double UtilityAIVector2AngleSearchCriterion::get_max_angle_degrees() const {
    return _max_angle_degrees;
}


// Handing methods.

void UtilityAIVector2AngleSearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    Node2D* node2d = godot::Object::cast_to<Node2D>(node);
    if( node2d == nullptr ) return;

    _is_filtered = false;
    _score = 0.0;

    Vector2 node2d_direction_vector = Vector2(1,0).rotated(node2d->get_global_rotation()).normalized();

    double angle = _angle_to_direction_vector.angle_to(node2d_direction_vector);
    
    if( get_use_for_filtering() ) {
        _is_filtered = (angle < _min_angle_degrees || angle > _max_angle_degrees );
    }//endif do filtering

    if( get_use_for_scoring() ) {
        if( angle >= _max_angle_degrees ) {
            _score = 1.0;
        } else if( angle <= _min_angle_degrees) {
            _score = 0.0;
        } else {
            double angle_from_lower_limit = angle - _min_angle_degrees;
            _score = angle_from_lower_limit * _one_over_span_radians; 
        }
        if( get_activation_curve().is_valid()) {
            _score = sample_activation_curve(_score);
        }
    }//endif do scoring
    
    filter_out = _is_filtered;
    score = _score;
    
}