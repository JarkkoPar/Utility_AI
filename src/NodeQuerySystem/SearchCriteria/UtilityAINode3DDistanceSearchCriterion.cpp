#include "UtilityAINode3DDistanceSearchCriterion.h"
#include <godot_cpp/classes/node3d.hpp>
using namespace godot;



UtilityAINode3DDistanceSearchCriterion::UtilityAINode3DDistanceSearchCriterion() {
    _min_distance = 0.0;
    _max_distance = 100.0;
    _min_distance_squared = 0.0;
    _max_distance_squared = _max_distance * _max_distance;

    _observer_node = nullptr;
}

UtilityAINode3DDistanceSearchCriterion::~UtilityAINode3DDistanceSearchCriterion() {
    _observer_node = nullptr;
}


// Getters and setters.

void UtilityAINode3DDistanceSearchCriterion::set_observer_nodepath( NodePath observer_nodepath ) {
    _observer_nodepath = observer_nodepath;
}


NodePath UtilityAINode3DDistanceSearchCriterion::get_observer_nodepath() const {
    return _observer_nodepath;
}


void UtilityAINode3DDistanceSearchCriterion::set_min_distance( double min_distance ) {
    if( _min_distance < 0.0 ) return;
    _min_distance = min_distance;
    _min_distance_squared = _min_distance * _min_distance;
}


double UtilityAINode3DDistanceSearchCriterion::get_min_distance() const {
    return _min_distance;
}


void UtilityAINode3DDistanceSearchCriterion::set_max_distance( double max_distance ) {
    if( max_distance < _min_distance ) return;
    _max_distance = max_distance;
    _max_distance_squared = _max_distance * _max_distance;
}


double UtilityAINode3DDistanceSearchCriterion::get_max_distance() const {
    return _max_distance;
}


// Handing methods.

void UtilityAINode3DDistanceSearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    Node3D* node3d = godot::Object::cast_to<Node3D>(node);
    if( node3d == nullptr ) return;
    

    
    filter_out = _is_filtered;
    score = _score;
}