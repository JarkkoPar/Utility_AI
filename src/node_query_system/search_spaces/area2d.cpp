#include "area2d.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


UtilityAIArea2DSearchSpace::UtilityAIArea2DSearchSpace() {
    _area2d = nullptr;
}


UtilityAIArea2DSearchSpace::~UtilityAIArea2DSearchSpace() {
}


void UtilityAIArea2DSearchSpace::_bind_methods() {

    ADD_SUBGROUP("Configuration","");

    ClassDB::bind_method(D_METHOD("set_area2d", "area2D"), &UtilityAIArea2DSearchSpace::set_area2d);
    ClassDB::bind_method(D_METHOD("get_area2d"), &UtilityAIArea2DSearchSpace::get_area2d);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "area2d", PROPERTY_HINT_NODE_TYPE, "Area2D"), "set_area2d", "get_area2d");

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

void UtilityAIArea2DSearchSpace::set_area2d( Area2D* area2d ) {
    _area2d = area2d;
}


Area2D* UtilityAIArea2DSearchSpace::get_area2d() const {
    return _area2d;
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
    ERR_FAIL_COND_MSG( !UtilityFunctions::is_instance_valid(_area2d) || _area2d == nullptr, "UtilityAIArea2DSearchSpace::_initialize_search_space() - Error, the node for the Area2D has not been set.");
    
    // Connect to the area entered and exited signals.
    Error error_visibility_volume_on_entered = _area2d->connect("area_entered", Callable(this, "on_area_entered"));
    Error error_visibility_volume_on_exited  = _area2d->connect("area_exited", Callable(this, "on_area_exited"));

}



void UtilityAIArea2DSearchSpace::_uninitialize_search_space() {
    if( _area2d != nullptr ) {
        _area2d->disconnect("area_entered", Callable(this, "on_area_entered"));
        _area2d->disconnect("area_exited", Callable(this, "on_area_exited"));
    }
    _area2d = nullptr;
}

