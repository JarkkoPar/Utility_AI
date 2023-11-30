#include "UtilityAIArea2DSearchSpace.h"

using namespace godot;


UtilityAIArea2DSearchSpace::UtilityAIArea2DSearchSpace() {
    _area2d_node = nullptr;
}


UtilityAIArea2DSearchSpace::~UtilityAIArea2DSearchSpace() {
}


void UtilityAIArea2DSearchSpace::_bind_methods() {

    ADD_SUBGROUP("Configuration","");

    ClassDB::bind_method(D_METHOD("set_area2d_nodepath", "area2D_nodepath"), &UtilityAIArea2DSearchSpace::set_area2d_nodepath);
    ClassDB::bind_method(D_METHOD("get_area2d_nodepath"), &UtilityAIArea2DSearchSpace::get_area2d_nodepath);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "area2d_nodepath", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Area2D"), "set_area2d_nodepath","get_area2d_nodepath");

    ClassDB::bind_method(D_METHOD("on_area_entered", "area"), &UtilityAIArea2DSearchSpace::on_area_entered);
    ClassDB::bind_method(D_METHOD("on_area_exited", "area"), &UtilityAIArea2DSearchSpace::on_area_exited);

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_intersecting_areas", "intersecting_areas"), &UtilityAIArea2DSearchSpace::set_intersecting_areas);
    ClassDB::bind_method(D_METHOD("get_intersecting_areas"), &UtilityAIArea2DSearchSpace::get_intersecting_areas);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "intersecting_areas", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Area2D")), "set_intersecting_areas","get_intersecting_areas");
}


void UtilityAIArea2DSearchSpace::on_area_entered(Area2D* area ) {
    if( area == nullptr ) {
        return;
    }
    if( _intersecting_areas.has(area) ) {
        return;
    }   
    _intersecting_areas.push_back(area);
}


void UtilityAIArea2DSearchSpace::on_area_exited(Area2D* area ) {
    if( area == nullptr ) {
        return;
    }
    if( !_intersecting_areas.has(area ) ) {
        return;
    }
    int index = _intersecting_areas.find(area);
    if( index < 0 ) {
        return;
    }
    _intersecting_areas.remove_at(index);
}
    
// Getters and setters for attributes.

void UtilityAIArea2DSearchSpace::set_area2d_nodepath( NodePath area2d_nodepath ) {
    _area2d_nodepath = area2d_nodepath;
}


NodePath UtilityAIArea2DSearchSpace::get_area2d_nodepath() const {
    return _area2d_nodepath;
}


void UtilityAIArea2DSearchSpace::set_intersecting_areas( TypedArray<Area2D> intersecting_areas ) {
    _intersecting_areas = intersecting_areas;
}


TypedArray<Area2D> UtilityAIArea2DSearchSpace::get_intersecting_areas() const {
    return _intersecting_areas;
}


// Handling methods.

TypedArray<Node> UtilityAIArea2DSearchSpace::get_searchspace_nodes() const {
    return _intersecting_areas;
}


void UtilityAIArea2DSearchSpace::_initialize_search_space() {
    Node* node = get_node_or_null(_area2d_nodepath);
    ERR_FAIL_COND_MSG( node == nullptr, "UtilityAIArea2DSearchSpace::_initialize_search_space() - Error, the nodepath for the Area2D has not been set.");
    _area2d_node = godot::Object::cast_to<Area2D>(node);
    ERR_FAIL_COND_MSG( _area2d_node == nullptr, "UtilityAIArea2DSearchSpace::_initialize_sensor() - Error, the node set as the Area2D is not of type Area2D.");
    
    // Connect to the area entered and exited signals.
    Error error_visibility_volume_on_entered = _area2d_node->connect("area_entered", Callable(this, "on_area_entered"));
    Error error_visibility_volume_on_exited  = _area2d_node->connect("area_exited", Callable(this, "on_area_exited"));

}



void UtilityAIArea2DSearchSpace::_uninitialize_search_space() {
    if( _area2d_node != nullptr ) {
        _area2d_node->disconnect("area_entered", Callable(this, "on_area_entered"));
        _area2d_node->disconnect("area_exited", Callable(this, "on_area_exited"));
    }
    _area2d_node = nullptr;
}

