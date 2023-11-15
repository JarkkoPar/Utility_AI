#ifndef UtilityAINavigation3DPointGridSearchSpaces_H_INCLUDED
#define UtilityAINavigation3DPointGridSearchSpaces_H_INCLUDED 

#include "UtilityAINQSSearchSpaces.h"
#include <godot_cpp/classes/node3d.hpp>

namespace godot {

class UtilityAINavigation3DPointGridSearchSpaces : public UtilityAINQSSearchSpaces {
    GDCLASS(UtilityAINavigation3DPointGridSearchSpaces, UtilityAINQSSearchSpaces)

    
public:
    UtilityAINavigation3DPointGridSearchSpaces();
    ~UtilityAINavigation3DPointGridSearchSpaces();

    // Godot virtuals.
    void _ready();    
    
    // Getters and setters for attributes.

    void set_show_debug_info( bool show_debug_info );
    bool get_show_debug_info() const;

    void set_navigation_map_rid( RID navigation_map_rid );
    RID  get_navigation_map_rid() const;

    void set_from_vector3( Vector3 from_vector );
    Vector3 get_from_vector3() const;

    void set_offset_vector3( Vector3 offset );
    Vector3 get_offset_vector3() const;


    void set_direction_vector3( Vector3 direction_vector );
    Vector3 get_direction_vector3() const;

    void set_grid_size( double grid_size );
    double get_grid_size() const;

    
    void set_use_owner_global_position_and_orientation( bool use_owner_global_position_and_orientation );
    bool get_use_owner_global_position_and_orientation() const;

    void set_point_grid( TypedArray<Node3D> point_grid );
    TypedArray<Node3D> get_point_grid() const;

    virtual TypedArray<Node> get_searchspace_nodes() const override;

    // Handling methods.

    virtual void create_point_grid();
    virtual void create_debug_info_nodes();


private:
    bool                _show_debug_info;
    RID                 _navigation_map_rid;
    double              _y_offset;
    double              _grid_size;
    Vector3             _from_vector;
    Vector3             _direction_vector;
    Vector3             _offset_vector;
    
    bool                _use_owner_global_position_and_orientation;
protected:
    static void _bind_methods();

    virtual void _initialize_search_space() override;

    Node3D*             _point_grid_parent_node;
    TypedArray<Node3D>  _point_grid;
    
};

}


#endif 
