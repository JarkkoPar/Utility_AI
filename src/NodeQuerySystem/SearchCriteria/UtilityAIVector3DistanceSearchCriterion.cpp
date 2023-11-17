#include "UtilityAIVector3DistanceSearchCriterion.h"
#include <godot_cpp/classes/node3d.hpp>

using namespace godot;


UtilityAIVector3DistanceSearchCriterion::UtilityAIVector3DistanceSearchCriterion() {
    _min_distance = 0.0;
    _max_distance = 100.0;
    _min_distance_squared = 0.0;
    _max_distance_squared = _max_distance * _max_distance;
    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
    _distance_to_vector = Vector3(0.0,0.0,0.0);
}


UtilityAIVector3DistanceSearchCriterion::~UtilityAIVector3DistanceSearchCriterion() {

}


void UtilityAIVector3DistanceSearchCriterion::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_distance_to_vector", "distance_to_vector"), &UtilityAIVector3DistanceSearchCriterion::set_distance_to_vector);
    ClassDB::bind_method(D_METHOD("get_distance_to_vector"), &UtilityAIVector3DistanceSearchCriterion::get_distance_to_vector);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "distance_to_vector", PROPERTY_HINT_NONE), "set_distance_to_vector","get_distance_to_vector");
    
    ClassDB::bind_method(D_METHOD("set_min_distance", "min_distance"), &UtilityAIVector3DistanceSearchCriterion::set_min_distance);
    ClassDB::bind_method(D_METHOD("get_min_distance"), &UtilityAIVector3DistanceSearchCriterion::get_min_distance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_distance", PROPERTY_HINT_NONE), "set_min_distance","get_min_distance");
    
    ClassDB::bind_method(D_METHOD("set_max_distance", "max_distance"), &UtilityAIVector3DistanceSearchCriterion::set_max_distance);
    ClassDB::bind_method(D_METHOD("get_max_distance"), &UtilityAIVector3DistanceSearchCriterion::get_max_distance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_distance", PROPERTY_HINT_NONE), "set_max_distance","get_max_distance");
    
    
}


void UtilityAIVector3DistanceSearchCriterion::_initialize_criterion() {

}


// Getters and setters.

void UtilityAIVector3DistanceSearchCriterion::set_distance_to_vector( Vector3 distance_to_vector ) {
    _distance_to_vector = distance_to_vector;
}


Vector3 UtilityAIVector3DistanceSearchCriterion::get_distance_to_vector() const {
    return _distance_to_vector;
}


void UtilityAIVector3DistanceSearchCriterion::set_min_distance( double min_distance ) {
    if( _min_distance < 0.0 ) return;
    if( _min_distance >= _max_distance ) return;

    _min_distance = min_distance;
    _min_distance_squared = _min_distance * _min_distance;

    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
}


double UtilityAIVector3DistanceSearchCriterion::get_min_distance() const {
    return _min_distance;
}


void UtilityAIVector3DistanceSearchCriterion::set_max_distance( double max_distance ) {
    if( max_distance <= _min_distance ) return;
    _max_distance = max_distance;
    _max_distance_squared = _max_distance * _max_distance;
    
    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
}


double UtilityAIVector3DistanceSearchCriterion::get_max_distance() const {
    return _max_distance;
}


// Handing methods.

void UtilityAIVector3DistanceSearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    Node3D* node3d = godot::Object::cast_to<Node3D>(node);
    if( node3d == nullptr ) return;

    _is_filtered = false;
    _score = 0.0;

    Vector3 from_to = node3d->get_global_position() - _distance_to_vector;
    double distance_squared = from_to.length_squared();
    
    if( get_use_for_filtering() ) {
        _is_filtered = (distance_squared < _min_distance_squared || distance_squared > _max_distance_squared);
    }//endif do filtering

    if( get_use_for_scoring() ) {
        if( distance_squared >= _max_distance_squared ) {
            _score = 1.0;
        } else if( distance_squared <= _min_distance_squared) {
            _score = 0.0;
        } else {
            double distance_from_lower_limit = distance_squared - _min_distance_squared;
            _score = distance_from_lower_limit * _one_over_span_length; 
        }
        if( get_activation_curve().is_valid()) {
            _score = sample_activation_curve(_score);
        }
    }//endif do scoring
    
    filter_out = _is_filtered;
    score = _score;
    
}