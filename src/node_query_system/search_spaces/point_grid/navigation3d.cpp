#include "navigation3d.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/script.hpp>

using namespace godot;


UtilityAINavigation3DPointGridSearchSpace::UtilityAINavigation3DPointGridSearchSpace() {
    _direction_vector = Vector3( 0.0, 0.0, -1.0 );
    _from_vector = Vector3( 0.0, 0.0, 0.0 );
    _offset_vector = Vector3(0.0,0.0,0.0);
    _grid_size = Vector3(15.0f, 0.0f, 15.0f);
    _point_grid_parent_node = nullptr; 
    _use_owner_global_position_and_orientation = true;
    _point_grid_base_spacing_vector = Vector3(2.0f, 1.0f, 1.0f);
    set_point_grid_lattice_type(UtilityAINavigation3DPointGridSearchSpaceLatticeType::SQUARE);
    _point_grid_type = UtilityAINavigation3DPointGridSearchSpaceType::RECTANGLE;
}


UtilityAINavigation3DPointGridSearchSpace::~UtilityAINavigation3DPointGridSearchSpace() {
    for( int i = 0; i < _point_grid.size(); ++i ) {
        Node3D* node = godot::Object::cast_to<Node3D>(_point_grid[i]);
        memfree(node);
        _point_grid[i] = nullptr;
    }//endfor point grid points
    _point_grid.clear();
    /**
    if( _point_grid_parent_node != nullptr ) {
        memfree(_point_grid_parent_node);
        _point_grid_parent_node = nullptr;
    }
    /**/
}


void UtilityAINavigation3DPointGridSearchSpace::_bind_methods() {

    ADD_SUBGROUP("Configuration","");

    ClassDB::bind_method(D_METHOD("set_point_grid_parent_node", "point_grid_parent_node"), &UtilityAINavigation3DPointGridSearchSpace::set_point_grid_parent_node);
    ClassDB::bind_method(D_METHOD("get_point_grid_parent_node"), &UtilityAINavigation3DPointGridSearchSpace::get_point_grid_parent_node);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "point_grid_parent_node", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_point_grid_parent_node","get_point_grid_parent_node");

    ClassDB::bind_method(D_METHOD("set_point_grid_type", "point_grid_type"), &UtilityAINavigation3DPointGridSearchSpace::set_point_grid_type);
    ClassDB::bind_method(D_METHOD("get_point_grid_type"), &UtilityAINavigation3DPointGridSearchSpace::get_point_grid_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "point_grid_type", PROPERTY_HINT_ENUM,"Rectangle:0,Circle:1"), "set_point_grid_type","get_point_grid_type");

    ClassDB::bind_method(D_METHOD("set_grid_size", "grid_size"), &UtilityAINavigation3DPointGridSearchSpace::set_grid_size);
    ClassDB::bind_method(D_METHOD("get_grid_size"), &UtilityAINavigation3DPointGridSearchSpace::get_grid_size);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "grid_size", PROPERTY_HINT_NONE), "set_grid_size","get_grid_size");

    ClassDB::bind_method(D_METHOD("set_point_grid_lattice_type", "point_grid_lattice_type"), &UtilityAINavigation3DPointGridSearchSpace::set_point_grid_lattice_type);
    ClassDB::bind_method(D_METHOD("get_point_grid_lattice_type"), &UtilityAINavigation3DPointGridSearchSpace::get_point_grid_lattice_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "point_grid_lattice_type", PROPERTY_HINT_ENUM,"Square:0,Triangular:1,CenteredRectangular:2,Rectangular:3,Custom:4"), "set_point_grid_lattice_type","get_point_grid_lattice_type");

    ClassDB::bind_method(D_METHOD("set_point_grid_base_spacing_vector", "point_grid_base_spacing_vector"), &UtilityAINavigation3DPointGridSearchSpace::set_point_grid_base_spacing_vector3);
    ClassDB::bind_method(D_METHOD("get_point_grid_base_spacing_vector"), &UtilityAINavigation3DPointGridSearchSpace::get_point_grid_base_spacing_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "point_grid_base_spacing_vector", PROPERTY_HINT_NONE), "set_point_grid_base_spacing_vector","get_point_grid_base_spacing_vector");

    ClassDB::bind_method(D_METHOD("set_point_grid_lattice_vector", "point_grid_lattice_vector"), &UtilityAINavigation3DPointGridSearchSpace::set_point_grid_lattice_vector3);
    ClassDB::bind_method(D_METHOD("get_point_grid_lattice_vector"), &UtilityAINavigation3DPointGridSearchSpace::get_point_grid_lattice_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "point_grid_lattice_vector", PROPERTY_HINT_NONE), "set_point_grid_lattice_vector","get_point_grid_lattice_vector");


    //ClassDB::bind_method(D_METHOD("set_from_vector", "from_vector"), &UtilityAINavigation3DPointGridSearchSpace::set_from_vector3);
    //ClassDB::bind_method(D_METHOD("get_from_vector"), &UtilityAINavigation3DPointGridSearchSpace::get_from_vector3);
    //ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "from_vector", PROPERTY_HINT_NONE), "set_from_vector","get_from_vector");

    ClassDB::bind_method(D_METHOD("set_offset_vector", "offset_vector"), &UtilityAINavigation3DPointGridSearchSpace::set_offset_vector3);
    ClassDB::bind_method(D_METHOD("get_offset_vector"), &UtilityAINavigation3DPointGridSearchSpace::get_offset_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "offset_vector", PROPERTY_HINT_NONE), "set_offset_vector","get_offset_vector");

    ClassDB::bind_method(D_METHOD("set_use_owner_global_position_and_orientation", "use_owner_global_position_and_orientation"), &UtilityAINavigation3DPointGridSearchSpace::set_use_owner_global_position_and_orientation);
    ClassDB::bind_method(D_METHOD("get_use_owner_global_position_and_orientation"), &UtilityAINavigation3DPointGridSearchSpace::get_use_owner_global_position_and_orientation);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_owner_global_position_and_orientation", PROPERTY_HINT_NONE), "set_use_owner_global_position_and_orientation","get_use_owner_global_position_and_orientation");

    ClassDB::bind_method(D_METHOD("set_navigation_map_rid", "navigation_map_rid"), &UtilityAINavigation3DPointGridSearchSpace::set_navigation_map_rid);
    ClassDB::bind_method(D_METHOD("get_navigation_map_rid"), &UtilityAINavigation3DPointGridSearchSpace::get_navigation_map_rid);
    ADD_PROPERTY(PropertyInfo(Variant::RID, "navigation_map_rid", PROPERTY_HINT_NONE), "set_navigation_map_rid","get_navigation_map_rid");

    ADD_SUBGROUP("Debugging","");

    //ClassDB::bind_method(D_METHOD("set_show_debug_info", "show_debug_info"), &UtilityAINavigation3DPointGridSearchSpace::set_show_debug_info);
    //ClassDB::bind_method(D_METHOD("get_show_debug_info"), &UtilityAINavigation3DPointGridSearchSpace::get_show_debug_info);
    //ADD_PROPERTY(PropertyInfo(Variant::BOOL, "show_debug_info", PROPERTY_HINT_NONE), "set_show_debug_info","get_show_debug_info");

    ClassDB::bind_method(D_METHOD("set_from_vector", "from_vector"), &UtilityAINavigation3DPointGridSearchSpace::set_from_vector3);
    ClassDB::bind_method(D_METHOD("get_from_vector"), &UtilityAINavigation3DPointGridSearchSpace::get_from_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "from_vector", PROPERTY_HINT_NONE), "set_from_vector","get_from_vector");

    ClassDB::bind_method(D_METHOD("set_direction_vector", "direction_vector"), &UtilityAINavigation3DPointGridSearchSpace::set_direction_vector3);
    ClassDB::bind_method(D_METHOD("get_direction_vector"), &UtilityAINavigation3DPointGridSearchSpace::get_direction_vector3);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "direction_vector", PROPERTY_HINT_NONE), "set_direction_vector","get_direction_vector");

    ClassDB::bind_method(D_METHOD("set_point_grid", "point_grid"), &UtilityAINavigation3DPointGridSearchSpace::set_point_grid);
    ClassDB::bind_method(D_METHOD("get_point_grid"), &UtilityAINavigation3DPointGridSearchSpace::get_point_grid);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "point_grid", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Node3D")), "set_point_grid","get_point_grid");

}

// Godot virtuals.

void UtilityAINavigation3DPointGridSearchSpace::_ready() {
    //if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    initialize_search_space();
    //create_point_grid();
    
}

// Getters and setters.

void UtilityAINavigation3DPointGridSearchSpace::set_point_grid_type( int point_grid_type ) {
    _point_grid_type = point_grid_type;
}

int  UtilityAINavigation3DPointGridSearchSpace::get_point_grid_type() const {
    return _point_grid_type;
}

void UtilityAINavigation3DPointGridSearchSpace::set_point_grid_lattice_type( int point_grid_lattice_type ) {
    _point_grid_lattice_type = point_grid_lattice_type;
    switch( point_grid_lattice_type ) {
        case UtilityAINavigation3DPointGridSearchSpaceLatticeType::SQUARE: {
            _point_grid_base_spacing_vector = Vector3(2.0f, 1.0f, 1.0f );
            _point_grid_lattice_vector = Vector3(1.0f, 0.0f, 0.0f ); 
        }
        break;
        case UtilityAINavigation3DPointGridSearchSpaceLatticeType::TRIANGULAR: {
            _point_grid_base_spacing_vector = Vector3(1.0f, 1.0f, 2.0f );
            _point_grid_lattice_vector = Vector3(-0.5f, 0.0f, 1.0f );
        }
        break;
        case UtilityAINavigation3DPointGridSearchSpaceLatticeType::CENTERED_RECTANGULAR: {
            _point_grid_base_spacing_vector = Vector3(2.0f, 1.0f, 1.0f );
            _point_grid_lattice_vector = Vector3(1.0f, 0.0f, 0.5f );
        }
        break;
        case UtilityAINavigation3DPointGridSearchSpaceLatticeType::RECTANGULAR: {
            _point_grid_base_spacing_vector = Vector3(2.0f, 1.0f, 0.5f );
            _point_grid_lattice_vector = Vector3(1.0f, 0.0f, 0.0f );
        }
        break;
        default: {
            // Custom.
        }
        break;
    }
}

int  UtilityAINavigation3DPointGridSearchSpace::get_point_grid_lattice_type() const {
    return _point_grid_lattice_type;
}

void UtilityAINavigation3DPointGridSearchSpace::set_point_grid_base_spacing_vector3( Vector3 point_grid_base_spacing_vector ) {
    if( _point_grid_base_spacing_vector.x > 0.0f && _point_grid_base_spacing_vector.y > 0.0f && _point_grid_base_spacing_vector.z > 0.0f ) {
        _point_grid_base_spacing_vector = point_grid_base_spacing_vector;
    }
}

Vector3 UtilityAINavigation3DPointGridSearchSpace::get_point_grid_base_spacing_vector3() const {
    return _point_grid_base_spacing_vector;
}


void UtilityAINavigation3DPointGridSearchSpace::set_point_grid_lattice_vector3( Vector3 point_grid_lattice_vector ) {
    _point_grid_lattice_vector = point_grid_lattice_vector;
}

Vector3 UtilityAINavigation3DPointGridSearchSpace::get_point_grid_lattice_vector3() const {
    return _point_grid_lattice_vector;
}

void UtilityAINavigation3DPointGridSearchSpace::set_grid_size( Vector3 grid_size ) {
    _grid_size = grid_size;
}


Vector3 UtilityAINavigation3DPointGridSearchSpace::get_grid_size() const {
    return _grid_size;
}


void UtilityAINavigation3DPointGridSearchSpace::set_navigation_map_rid( RID navigation_map_rid ) {
    _navigation_map_rid = navigation_map_rid;
}


RID  UtilityAINavigation3DPointGridSearchSpace::get_navigation_map_rid() const {
    return _navigation_map_rid;
}

TypedArray<Node> UtilityAINavigation3DPointGridSearchSpace::get_searchspace_nodes() const {
    /*if( _use_owner_global_position_and_orientation && get_owner() != nullptr ) {
        Node3D* owner3d = godot::Object::cast_to<Node3D>(get_owner());
        if( owner3d != nullptr ) {
            _from_vector = owner3d->get_global_position();
            Transform3D owner_global_transform = owner3d->get_global_transform();
            Basis owner_basis = owner_global_transform.get_basis();
            //_direction_vector = -owner_basis.get_column(2);
        }//endif owner is node3d derived
    }//endif use owner global position and orientation
    _point_grid_parent_node->set_global_position(_from_vector + _offset_vector);
    /**/
    return _point_grid;
}


void UtilityAINavigation3DPointGridSearchSpace::set_from_vector3( Vector3 from_vector ) {
    _from_vector = from_vector;
}


Vector3 UtilityAINavigation3DPointGridSearchSpace::get_from_vector3() const {
    return _from_vector;
}


void UtilityAINavigation3DPointGridSearchSpace::set_direction_vector3( Vector3 direction_vector ) {
    _direction_vector = direction_vector;
}


Vector3 UtilityAINavigation3DPointGridSearchSpace::get_direction_vector3() const {
    return _direction_vector;
}


void UtilityAINavigation3DPointGridSearchSpace::set_offset_vector3( Vector3 offset ) {
    _offset_vector = offset;
}


Vector3 UtilityAINavigation3DPointGridSearchSpace::get_offset_vector3() const {
    return _offset_vector;
}

void UtilityAINavigation3DPointGridSearchSpace::set_point_grid_parent_node( Node3D* point_grid_parent_node ) {
    _point_grid_parent_node = point_grid_parent_node;
}

Node3D* UtilityAINavigation3DPointGridSearchSpace::get_point_grid_parent_node() const {
    return _point_grid_parent_node;
}

void UtilityAINavigation3DPointGridSearchSpace::set_use_owner_global_position_and_orientation( bool use_owner_global_position_and_orientation ) {
    _use_owner_global_position_and_orientation = use_owner_global_position_and_orientation;
}


bool UtilityAINavigation3DPointGridSearchSpace::get_use_owner_global_position_and_orientation() const {
    return _use_owner_global_position_and_orientation;
}


void UtilityAINavigation3DPointGridSearchSpace::set_point_grid( TypedArray<Node3D> point_grid ) {
    _point_grid = point_grid;
}


TypedArray<Node3D> UtilityAINavigation3DPointGridSearchSpace::get_point_grid() const {
    return _point_grid;
}


// Handling methods.

void UtilityAINavigation3DPointGridSearchSpace::create_point_grid() {
    // This creates the Node3D nodes as hidden child nodes.

    // First create the Vector array for the ideal grid.
    _point_grid_default_positions.clear();
    switch( _point_grid_type ) {
        case UtilityAINavigation3DPointGridSearchSpaceType::CIRCLE: {

        }
        break;
        default: {
            // Rectangle.
            create_rectangular_point_grid();
        }
    }//end switch point grid type
    
    // If there is a debug child under the search space node, make duplicates of it
    // under the search space parent node.
    Node3D* template_node = nullptr;
    for( int i = 0; i < get_child_count(); ++i ) {
        if(Node3D* dbnode = godot::Object::cast_to<Node3D>(get_child(i))){
            if( dbnode->get_name() == StringName("DEBUG")) {
                template_node = dbnode;
                break;
            }
        }//endif node3d
    }//endfor childnodes
    if( template_node == nullptr ) {
        template_node = memnew(Node3D);
        template_node->set_name("___UTILITYAI_DELETE___");
    }

    // Ensure that score and is_filtered are available for debug.
    template_node->set("score", 0.0f);
    template_node->set("is_filtered", false);

    create_point_grid_nodes(template_node);

    if( template_node->get_name() == StringName("___UTILITYAI_DELETE___")) {
        memdelete(template_node);
        template_node = nullptr;
    }
}


void UtilityAINavigation3DPointGridSearchSpace::create_point_grid_nodes(Node3D* template_node) {
    
    for( int i = 0; i < _point_grid_default_positions.size(); ++i ) {
        Node3D* new_node = godot::Object::cast_to<Node3D>(template_node->duplicate(15));
        if( new_node == nullptr ) {
            ERR_FAIL_MSG("UtilityAINavigation3DPointGridSearchSpace::create_point_grid_nodes(): Error, could not duplicate template node. Out of memory?");
            return;
        }//endif nullptr
        //new_node->set_script(template_node->get_script());
        _point_grid_parent_node->add_child(new_node);//, false, godot::Node::InternalMode::INTERNAL_MODE_BACK );
        new_node->set_position(_point_grid_default_positions[i]);
        _point_grid.push_back(new_node);
    }//endfor default positions
}


void UtilityAINavigation3DPointGridSearchSpace::create_rectangular_point_grid() {
    _point_grid_default_positions.clear();
    float y = -0.5f * _grid_size.y;
    float max_y = 0.5f * _grid_size.y;
    float max_x = 0.5f * _grid_size.x;
    float max_z = 0.5f * _grid_size.z;
    while( _grid_size.y >= 0.0f && y <= max_y ) {
        float x = -0.5f * _grid_size.x;
        while( _grid_size.x >= 0.0f && x <= max_x ) {
            float z = -0.5f * _grid_size.z;
            while( _grid_size.z >= 0.0f && z <= max_z ) {
                Vector3 new_point = Vector3(x, y, z);
                _point_grid_default_positions.push_back(new_point);
                Vector3 lattice_point = new_point + _point_grid_lattice_vector;
                _point_grid_default_positions.push_back(lattice_point);

                z += _point_grid_base_spacing_vector.z;
            }//endwhile z
            x += _point_grid_base_spacing_vector.x;
        }//endwhile y
        y += _point_grid_base_spacing_vector.y;
    }//endwhile x
}


void UtilityAINavigation3DPointGridSearchSpace::_initialize_search_space() {
    if( _point_grid_parent_node == nullptr ) return;

    // Create the node3d's for the grid.
    create_point_grid();
    _navigation_map_rid = get_viewport()->get_world_3d()->get_navigation_map();
    
}

