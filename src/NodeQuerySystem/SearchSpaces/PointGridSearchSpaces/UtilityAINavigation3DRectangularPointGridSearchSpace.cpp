#include "UtilityAINavigation3DRectangularPointGridSearchSpace.h"

using namespace godot;


UtilityAINavigation3DRectangularPointGridSearchSpace::UtilityAINavigation3DRectangularPointGridSearchSpace() {
    _rectangle_width = 10.0;
    _rectangle_height = 10.0;
}


UtilityAINavigation3DRectangularPointGridSearchSpace::~UtilityAINavigation3DRectangularPointGridSearchSpace() {


}


void UtilityAINavigation3DRectangularPointGridSearchSpace::_bind_methods() {
    ADD_SUBGROUP("Configuration","");

    ClassDB::bind_method(D_METHOD("set_rectangle_width", "rectangle_width"), &UtilityAINavigation3DRectangularPointGridSearchSpace::set_rectangle_width);
    ClassDB::bind_method(D_METHOD("get_rectangle_width"), &UtilityAINavigation3DRectangularPointGridSearchSpace::get_rectangle_width);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rectangle_width", PROPERTY_HINT_NONE), "set_rectangle_width","get_rectangle_width");

    ClassDB::bind_method(D_METHOD("set_rectangle_height", "rectangle_height"), &UtilityAINavigation3DRectangularPointGridSearchSpace::set_rectangle_height);
    ClassDB::bind_method(D_METHOD("get_rectangle_height"), &UtilityAINavigation3DRectangularPointGridSearchSpace::get_rectangle_height);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rectangle_height", PROPERTY_HINT_NONE), "set_rectangle_height","get_rectangle_height");

}

// Getters and setters.

void UtilityAINavigation3DRectangularPointGridSearchSpace::set_rectangle_width( double rectangle_width ) {
    if( rectangle_width <= 0.0 ) return;
    _rectangle_width = rectangle_width;
}


double UtilityAINavigation3DRectangularPointGridSearchSpace::get_rectangle_width() const {
    return _rectangle_width;
}


void UtilityAINavigation3DRectangularPointGridSearchSpace::set_rectangle_height( double rectangle_height ) {
    if( rectangle_height <= 0.0 ) return;
    _rectangle_height = rectangle_height;
}


double UtilityAINavigation3DRectangularPointGridSearchSpace::get_rectangle_height() const {
    return _rectangle_height;
}

// Handling methods.

void UtilityAINavigation3DRectangularPointGridSearchSpace::create_point_grid() {
    int x_points = _rectangle_width / get_grid_size();
    int z_points = _rectangle_height / get_grid_size();
    double half_width = _rectangle_width * 0.5;
    double half_height = _rectangle_height * 0.5;

    Vector3 right_vector = get_direction_vector3();
    right_vector.rotate( Vector3( 0.0, 1.0, 0.0 ), Math_PI * 0.5 );
    
    for( int x = 0; x < x_points; ++x ) {
        for( int z = 0; z < z_points; ++z ) {
            //Ref<Node3D> new_node;
            //new_node.instantiate();
            Node3D* new_node = memnew(Node3D);
            if( new_node == nullptr ) {
                ERR_FAIL_MSG("UtilityAINavigation3DRectangularPointGridSearchSpace::create_point_grid() - Failed, out of memory!");
            }
            _point_grid_parent_node->add_child(new_node);
            new_node->set_position( Vector3( -half_width + (double)x * get_grid_size(), 0.0, -half_height + (double)z * get_grid_size()));
            
            // Get the closest point for this gridpoint on the navigation map.

            _point_grid.push_back(new_node);
        }//endfor z
    }//endfor x
}
