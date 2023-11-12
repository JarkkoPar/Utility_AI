#include "UtilityAINavigation3DPointGridSearchSpaces.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;


UtilityAINavigation3DPointGridSearchSpaces::UtilityAINavigation3DPointGridSearchSpaces() {
    _show_debug_info = false;
    _direction_vector = Vector3( 0.0, 0.0, -1.0 );
    _from_vector = Vector3( 0.0, 0.0, 0.0 );

    _point_grid_parent_node = nullptr; 
}


UtilityAINavigation3DPointGridSearchSpaces::~UtilityAINavigation3DPointGridSearchSpaces() {
    for( int i = 0; i < _point_grid.size(); ++i ) {
        Node3D* node = godot::Object::cast_to<Node3D>(_point_grid[i]);
        memfree(node);
        _point_grid[i] = nullptr;
    }//endfor point grid points
    _point_grid.clear();
    if( _point_grid_parent_node != nullptr ) {
        memfree(_point_grid_parent_node);
        _point_grid_parent_node = nullptr;
    }
}


void UtilityAINavigation3DPointGridSearchSpaces::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_navigation_map_rid", "navigation_map_rid"), &UtilityAINavigation3DPointGridSearchSpaces::set_navigation_map_rid);
    ClassDB::bind_method(D_METHOD("get_navigation_map_rid"), &UtilityAINavigation3DPointGridSearchSpaces::get_navigation_map_rid);
    ADD_PROPERTY(PropertyInfo(Variant::RID, "navigation_map_rid", PROPERTY_HINT_NONE), "set_navigation_map_rid","get_navigation_map_rid");

    ClassDB::bind_method(D_METHOD("set_show_debug_info", "show_debug_info"), &UtilityAINavigation3DPointGridSearchSpaces::set_show_debug_info);
    ClassDB::bind_method(D_METHOD("get_show_debug_info"), &UtilityAINavigation3DPointGridSearchSpaces::get_show_debug_info);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "show_debug_info", PROPERTY_HINT_NONE), "set_show_debug_info","get_show_debug_info");

    ClassDB::bind_method(D_METHOD("set_from_vector", "from_vector"), &UtilityAINavigation3DPointGridSearchSpaces::set_from_vector3);
    ClassDB::bind_method(D_METHOD("get_from_vector"), &UtilityAINavigation3DPointGridSearchSpaces::get_from_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "from_vector", PROPERTY_HINT_NONE), "set_from_vector","get_from_vector");
    
    ClassDB::bind_method(D_METHOD("set_direction_vector", "direction_vector"), &UtilityAINavigation3DPointGridSearchSpaces::set_direction_vector3);
    ClassDB::bind_method(D_METHOD("get_direction_vector"), &UtilityAINavigation3DPointGridSearchSpaces::get_direction_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "direction_vector", PROPERTY_HINT_NONE), "set_direction_vector","get_direction_vector");
    
    ClassDB::bind_method(D_METHOD("set_y_offset", "y_offset"), &UtilityAINavigation3DPointGridSearchSpaces::set_y_offset);
    ClassDB::bind_method(D_METHOD("get_y_offset"), &UtilityAINavigation3DPointGridSearchSpaces::get_y_offset);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "y_offset", PROPERTY_HINT_RANGE,"0.0,100.0,or_greater"), "set_y_offset","get_y_offset");
    
    ClassDB::bind_method(D_METHOD("set_point_grid", "point_grid"), &UtilityAINavigation3DPointGridSearchSpaces::set_point_grid);
    ClassDB::bind_method(D_METHOD("get_point_grid"), &UtilityAINavigation3DPointGridSearchSpaces::get_point_grid);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "point_grid", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Node3D")), "set_point_grid","get_point_grid");

}

// Godot virtuals.

void UtilityAINavigation3DPointGridSearchSpaces::_ready() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    create_point_grid();
    if( _show_debug_info ) {
        create_debug_info_nodes();
    }

    _navigation_map_rid = get_viewport()->get_world_3d()->get_navigation_map();
    
}

// Getters and setters.

void UtilityAINavigation3DPointGridSearchSpaces::set_show_debug_info( bool show_debug_info ) {
    _show_debug_info = show_debug_info;
}


bool UtilityAINavigation3DPointGridSearchSpaces::get_show_debug_info() const {
    return _show_debug_info;
}

void UtilityAINavigation3DPointGridSearchSpaces::set_navigation_map_rid( RID navigation_map_rid ) {
    _navigation_map_rid = navigation_map_rid;
}


RID  UtilityAINavigation3DPointGridSearchSpaces::get_navigation_map_rid() const {
    return _navigation_map_rid;
}

TypedArray<Node> UtilityAINavigation3DPointGridSearchSpaces::get_searchspace_nodes() const {
    return _point_grid;
}


void UtilityAINavigation3DPointGridSearchSpaces::set_from_vector3( Vector3 from_vector ) {
    _from_vector = from_vector;
}


Vector3 UtilityAINavigation3DPointGridSearchSpaces::get_from_vector3() const {
    return _from_vector;
}


void UtilityAINavigation3DPointGridSearchSpaces::set_direction_vector3( Vector3 direction_vector ) {
    _direction_vector = direction_vector;
}


Vector3 UtilityAINavigation3DPointGridSearchSpaces::get_direction_vector3() const {
    return _direction_vector;
}


void UtilityAINavigation3DPointGridSearchSpaces::set_y_offset( double y_offset ) {
    _y_offset = y_offset;
}


double UtilityAINavigation3DPointGridSearchSpaces::get_y_offset() const {
    return _y_offset;
}


void UtilityAINavigation3DPointGridSearchSpaces::set_point_grid( TypedArray<Node3D> point_grid ) {
    _point_grid = point_grid;
}


TypedArray<Node3D> UtilityAINavigation3DPointGridSearchSpaces::get_point_grid() const {
    return _point_grid;
}


// Handling methods.

void UtilityAINavigation3DPointGridSearchSpaces::create_point_grid() {
}


void UtilityAINavigation3DPointGridSearchSpaces::create_debug_info_nodes() {
    for( int i = 0; i < _point_grid.size(); ++i ) {
        Node3D* grid_node = godot::Object::cast_to<Node3D>(get_child(i));
        if( grid_node == nullptr) {
            continue;
        }

        //Ref<MeshInstance3D> new_mesh_instance = memnew(MeshInstance3D);
        //Ref<Mesh> new_mesh; //= memnew(Mesh);
        //new_mesh.instantiate();
        
    }//endfor nodes
}


void UtilityAINavigation3DPointGridSearchSpaces::_initialize_search_space() {
    if( _point_grid_parent_node == nullptr ) {
        _point_grid_parent_node = memnew(Node3D);
        if( _point_grid_parent_node == nullptr ) {
            ERR_FAIL_MSG("UtilityAINavigation3DPointGridSearchSpaces::_initialize_search_space(): Unable to create the point grid parent node. Out of memory?");
        }
        // Add the node3d parent as an internal node.
        add_child(_point_grid_parent_node, false, InternalMode::INTERNAL_MODE_FRONT);
    }

    // Create the node3d's for the grid.
    create_point_grid();
}

