#include "UtilityAIDistanceToNode2DSearchCriterion.h"
#include <godot_cpp/classes/node2d.hpp>

using namespace godot;


UtilityAIDistanceToNode2DSearchCriterion::UtilityAIDistanceToNode2DSearchCriterion() {
    _min_distance = 0.0;
    _max_distance = 100.0;
    _min_distance_squared = 0.0;
    _max_distance_squared = _max_distance * _max_distance;
    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
    _distance_to = nullptr;
}


UtilityAIDistanceToNode2DSearchCriterion::~UtilityAIDistanceToNode2DSearchCriterion() {
    _distance_to = nullptr;
}


void UtilityAIDistanceToNode2DSearchCriterion::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_distance_to", "distance_to"), &UtilityAIDistanceToNode2DSearchCriterion::set_distance_to);
    ClassDB::bind_method(D_METHOD("get_distance_to"), &UtilityAIDistanceToNode2DSearchCriterion::get_distance_to);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "distance_to", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_distance_to", "get_distance_to");
    
    ClassDB::bind_method(D_METHOD("set_min_distance", "min_distance"), &UtilityAIDistanceToNode2DSearchCriterion::set_min_distance);
    ClassDB::bind_method(D_METHOD("get_min_distance"), &UtilityAIDistanceToNode2DSearchCriterion::get_min_distance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_distance", PROPERTY_HINT_NONE), "set_min_distance","get_min_distance");
    
    ClassDB::bind_method(D_METHOD("set_max_distance", "max_distance"), &UtilityAIDistanceToNode2DSearchCriterion::set_max_distance);
    ClassDB::bind_method(D_METHOD("get_max_distance"), &UtilityAIDistanceToNode2DSearchCriterion::get_max_distance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_distance", PROPERTY_HINT_NONE), "set_max_distance","get_max_distance");
    
    
}


void UtilityAIDistanceToNode2DSearchCriterion::_initialize_criterion() {
}


// Getters and setters.

void UtilityAIDistanceToNode2DSearchCriterion::set_distance_to( Node2D* distance_to ) {
    _distance_to = distance_to;
}


Node2D* UtilityAIDistanceToNode2DSearchCriterion::get_distance_to() const {
    return _distance_to;
}


void UtilityAIDistanceToNode2DSearchCriterion::set_min_distance( double min_distance ) {
    if( _min_distance < 0.0 ) return;
    if( _min_distance >= _max_distance ) return;

    _min_distance = min_distance;
    _min_distance_squared = _min_distance * _min_distance;

    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
}


double UtilityAIDistanceToNode2DSearchCriterion::get_min_distance() const {
    return _min_distance;
}


void UtilityAIDistanceToNode2DSearchCriterion::set_max_distance( double max_distance ) {
    if( max_distance <= _min_distance ) return;
    _max_distance = max_distance;
    _max_distance_squared = _max_distance * _max_distance;
    
    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
}


double UtilityAIDistanceToNode2DSearchCriterion::get_max_distance() const {
    return _max_distance;
}


// Handing methods.

void UtilityAIDistanceToNode2DSearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    if( _distance_to == nullptr ) return;
    Node2D* node2d = godot::Object::cast_to<Node2D>(node);
    if( node2d == nullptr ) return;
    
    _is_filtered = false;
    _score = 0.0;

    Vector2 from_to = node2d->get_global_position() - _distance_to->get_global_position();
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