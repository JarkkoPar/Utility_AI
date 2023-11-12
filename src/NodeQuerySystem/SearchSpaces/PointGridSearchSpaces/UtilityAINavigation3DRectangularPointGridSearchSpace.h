#ifndef UtilityAINavigation3DRectangularPointGridSearchSpace_H_INCLUDED
#define UtilityAINavigation3DRectangularPointGridSearchSpace_H_INCLUDED 

#include "UtilityAINavigation3DPointGridSearchSpaces.h"


namespace godot {

class UtilityAINavigation3DRectangularPointGridSearchSpace : public UtilityAINavigation3DPointGridSearchSpaces {
    GDCLASS(UtilityAINavigation3DRectangularPointGridSearchSpace, UtilityAINavigation3DPointGridSearchSpaces)

    
public:
    UtilityAINavigation3DRectangularPointGridSearchSpace();
    ~UtilityAINavigation3DRectangularPointGridSearchSpace();

    // Godot virtuals.
    //void _ready();    
    
    // Getters and setters for attributes.

    void set_rectangle_width( double rectangle_width );
    double get_rectangle_width() const;

    void set_rectangle_height( double rectangle_height );
    double get_rectangle_height() const;

    // Handling methods.

    virtual void create_point_grid() override;
    
private:
    double  _rectangle_width;
    double  _rectangle_height;
    //double  _grid_size;
protected:
    static void _bind_methods();

};

}


#endif 
