#ifndef UtilityAIPointGrid2DSearchSpaces_H_INCLUDED
#define UtilityAIPointGrid2DSearchSpaces_H_INCLUDED 

#include "../nqs.h"
#include <godot_cpp/classes/node2d.hpp>

namespace godot {

class UtilityAIPointGrid2DSearchSpace : public UtilityAINQSSearchSpaces {
    GDCLASS(UtilityAIPointGrid2DSearchSpace, UtilityAINQSSearchSpaces)

    
public:
    UtilityAIPointGrid2DSearchSpace();
    ~UtilityAIPointGrid2DSearchSpace();

    // Godot virtuals.
    void _ready();    
    
    // Getters and setters for attributes.

    void set_point_grid_type( int point_grid_type );
    int  get_point_grid_type() const;

    void set_point_grid_lattice_type( int point_grid_lattice_type );
    int  get_point_grid_lattice_type() const;

    void set_point_grid_lattice_vector2( Vector2 point_grid_lattice_vector );
    Vector2 get_point_grid_lattice_vector2() const;

    void set_point_grid_base_spacing_vector2( Vector2 grid_base_spacing_vector );
    Vector2 get_point_grid_base_spacing_vector2() const;

    void set_navigation_map_rid( RID navigation_map_rid );
    RID  get_navigation_map_rid() const;

    void set_offset_vector2( Vector2 offset );
    Vector2 get_offset_vector2() const;

    void set_point_grid_parent_node( Node2D* point_grid_parent_node );
    Node2D* get_point_grid_parent_node() const;

    void set_grid_spacing( Vector2 grid_spacing );
    Vector2 get_grid_spacing() const;

    void set_grid_size( Vector2 grid_size );
    Vector2 get_grid_size() const;

    void set_use_navigation_mesh_positions( bool use_navigation_mesh_positions );
    bool get_use_navigation_mesh_positions() const;

    void set_point_grid( TypedArray<Node2D> point_grid );
    TypedArray<Node2D> get_point_grid() const;

    virtual TypedArray<Node> get_searchspace_nodes() const override;

    // Handling methods.

    virtual void create_point_grid();
    void create_rectangular_point_grid();
    void create_point_grid_nodes( Node2D* template_node );

    enum UtilityAIPointGrid2DSearchSpaceType {
        RECTANGLE = 0,
        CIRCLE = 1,
    };

    enum UtilityAIPointGrid2DSearchSpaceLatticeType {
        SQUARE = 0,
        TRIANGULAR = 1,
        CENTERED_RECTANGULAR = 2,
        RECTANGULAR = 3,
        CUSTOM = 4,
    };

private:
    RID                 _navigation_map_rid;
    Vector2             _offset_vector;
    bool                _use_navigation_mesh_positions;

protected:
    static void _bind_methods();

    virtual void _initialize_search_space() override;
    virtual bool preprocess_search_space(uint64_t time_limit_timestamp_usec) override;
    
    Vector2             _grid_size;
    Vector2             _point_grid_base_spacing_vector;
    int                 _point_grid_lattice_type;
    Vector2             _point_grid_lattice_vector;

    int                 _point_grid_type;
    Node2D*             _point_grid_parent_node;
    TypedArray<Node2D>  _point_grid;

    std::vector<Vector2> _point_grid_default_positions; 
};

}


#endif 
