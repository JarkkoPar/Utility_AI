#include "UtilityAIArea3DSearchSpace.h"

using namespace godot;


UtilityAIArea3DSearchSpace::UtilityAIArea3DSearchSpace() {
    _area3d_node = nullptr;
}


UtilityAIArea3DSearchSpace::~UtilityAIArea3DSearchSpace() {
    
}


void UtilityAIArea3DSearchSpace::_bind_methods() {

    ADD_SUBGROUP("Configuration","");

    ClassDB::bind_method(D_METHOD("set_area3d_nodepath", "area3d_nodepath"), &UtilityAIArea3DSearchSpace::set_area3d_nodepath);
    ClassDB::bind_method(D_METHOD("get_area3d_nodepath"), &UtilityAIArea3DSearchSpace::get_area3d_nodepath);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "area3d_nodepath", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Area3D"), "set_area3d_nodepath","get_area3d_nodepath");

    ClassDB::bind_method(D_METHOD("on_area_entered", "area"), &UtilityAIArea3DSearchSpace::on_area_entered);
    ClassDB::bind_method(D_METHOD("on_area_exited", "area"), &UtilityAIArea3DSearchSpace::on_area_exited);

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_intersecting_areas", "intersecting_areas"), &UtilityAIArea3DSearchSpace::set_intersecting_areas);
    ClassDB::bind_method(D_METHOD("get_intersecting_areas"), &UtilityAIArea3DSearchSpace::get_intersecting_areas);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "intersecting_areas", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Area3D")), "set_intersecting_areas","get_intersecting_areas");
}


void UtilityAIArea3DSearchSpace::on_area_entered(Area3D* area ) {
    if( area == nullptr ) {
        return;
    }
    if( _intersecting_areas.has(area) ) {
        return;
    }   
    _intersecting_areas.push_back(area);
}


void UtilityAIArea3DSearchSpace::on_area_exited(Area3D* area ) {
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

void UtilityAIArea3DSearchSpace::set_area3d_nodepath( NodePath area3d_nodepath ) {
    _area3d_nodepath = area3d_nodepath;
}


NodePath UtilityAIArea3DSearchSpace::get_area3d_nodepath() const {
    return _area3d_nodepath;
}


void UtilityAIArea3DSearchSpace::set_intersecting_areas( TypedArray<Area3D> intersecting_areas ) {
    _intersecting_areas = intersecting_areas;
}


TypedArray<Area3D> UtilityAIArea3DSearchSpace::get_intersecting_areas() const {
    return _intersecting_areas;
}


// Handling methods.

TypedArray<Node> UtilityAIArea3DSearchSpace::get_searchspace_nodes() const {
    return _intersecting_areas;
}


void UtilityAIArea3DSearchSpace::_initialize_search_space() {
    Node* node = get_node_or_null(_area3d_nodepath);
    ERR_FAIL_COND_MSG( node == nullptr, "UtilityAIArea3DSearchSpace::_initialize_search_space() - Error, the nodepath for the Area3D has not been set.");
    _area3d_node = godot::Object::cast_to<Area3D>(node);
    ERR_FAIL_COND_MSG( _area3d_node == nullptr, "UtilityAIArea3DSearchSpace::_initialize_sensor() - Error, the node set as the Area3D is not of type Area3D.");
    
    // Connect to the area entered and exited signals.
    Error error_visibility_volume_on_entered = _area3d_node->connect("area_entered", Callable(this, "on_area_entered"));
    Error error_visibility_volume_on_exited  = _area3d_node->connect("area_exited", Callable(this, "on_area_exited"));

}


void UtilityAIArea3DSearchSpace::_uninitialize_search_space() {
    if( _area3d_node != nullptr ) {
        _area3d_node->disconnect("area_entered", Callable(this, "on_area_entered"));
        _area3d_node->disconnect("area_exited", Callable(this, "on_area_exited"));
    }
    _area3d_node = nullptr;
}

