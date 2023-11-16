#include "UtilityAINode2DDistanceSearchCriterion.h"
#include <godot_cpp/classes/node2d.hpp>

using namespace godot;


UtilityAINode2DDistanceSearchCriterion::UtilityAINode2DDistanceSearchCriterion() {
    _min_distance = 0.0;
    _max_distance = 100.0;
    _min_distance_squared = 0.0;
    _max_distance_squared = _max_distance * _max_distance;
    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
    _distance_to_node = nullptr;
}


UtilityAINode2DDistanceSearchCriterion::~UtilityAINode2DDistanceSearchCriterion() {
    _distance_to_node = nullptr;
}


void UtilityAINode2DDistanceSearchCriterion::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_distance_to_nodepath", "distance_to_nodepath"), &UtilityAINode2DDistanceSearchCriterion::set_distance_to_nodepath);
    ClassDB::bind_method(D_METHOD("get_distance_to_nodepath"), &UtilityAINode2DDistanceSearchCriterion::get_distance_to_nodepath);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "distance_to_nodepath", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Node2D"), "set_distance_to_nodepath","get_distance_to_nodepath");
    
    ClassDB::bind_method(D_METHOD("set_min_distance", "min_distance"), &UtilityAINode2DDistanceSearchCriterion::set_min_distance);
    ClassDB::bind_method(D_METHOD("get_min_distance"), &UtilityAINode2DDistanceSearchCriterion::get_min_distance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_distance", PROPERTY_HINT_NONE), "set_min_distance","get_min_distance");
    
    ClassDB::bind_method(D_METHOD("set_max_distance", "max_distance"), &UtilityAINode2DDistanceSearchCriterion::set_max_distance);
    ClassDB::bind_method(D_METHOD("get_max_distance"), &UtilityAINode2DDistanceSearchCriterion::get_max_distance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_distance", PROPERTY_HINT_NONE), "set_max_distance","get_max_distance");
    
    
}


void UtilityAINode2DDistanceSearchCriterion::_initialize_criterion() {
    Node* node = get_node_or_null(_distance_to_nodepath);
    if( node == nullptr ) return;
    _distance_to_node = godot::Object::cast_to<Node2D>(node);
}


// Getters and setters.

void UtilityAINode2DDistanceSearchCriterion::set_distance_to_nodepath( NodePath distance_to_nodepath ) {
    _distance_to_nodepath = distance_to_nodepath;
}


NodePath UtilityAINode2DDistanceSearchCriterion::get_distance_to_nodepath() const {
    return _distance_to_nodepath;
}


void UtilityAINode2DDistanceSearchCriterion::set_min_distance( double min_distance ) {
    if( _min_distance < 0.0 ) return;
    if( _min_distance >= _max_distance ) return;

    _min_distance = min_distance;
    _min_distance_squared = _min_distance * _min_distance;

    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
}


double UtilityAINode2DDistanceSearchCriterion::get_min_distance() const {
    return _min_distance;
}


void UtilityAINode2DDistanceSearchCriterion::set_max_distance( double max_distance ) {
    if( max_distance <= _min_distance ) return;
    _max_distance = max_distance;
    _max_distance_squared = _max_distance * _max_distance;
    
    _span_length = _max_distance_squared - _min_distance_squared;
    _one_over_span_length = 1.0 / _span_length;
}


double UtilityAINode2DDistanceSearchCriterion::get_max_distance() const {
    return _max_distance;
}


// Handing methods.

void UtilityAINode2DDistanceSearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    if( _distance_to_node == nullptr ) return;
    Node2D* node2d = godot::Object::cast_to<Node2D>(node);
    if( node2d == nullptr ) return;
    
    _is_filtered = false;
    _score = 0.0;

    Vector2 from_to = node2d->get_global_position() - _distance_to_node->get_global_position();
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