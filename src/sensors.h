#ifndef UtilityAISensors_H_INCLUDED
#define UtilityAISensors_H_INCLUDED 

#include "utility_ai.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAISensors : public UtilityAI {
    GDCLASS(UtilityAISensors, UtilityAI)

private:
    
    double _sensor_value;
    //bool   _use_absolute_value; // Place holder for when in Godot the Curve X-value can be adjusted to any range other than 0..1.
    
protected:
    static void _bind_methods();

public:
    UtilityAISensors();
    ~UtilityAISensors();
    
    // Godot virtuals.

    void _ready();

    void _exit_tree();

    // Handling methods.

    virtual void initialize_sensor();
    virtual void uninitialize_sensor() {}
    
    // Getters and setters for attributes.
    
    
    void set_sensor_value( double sensor_value );
    double get_sensor_value() const;

    //void set_use_absolute_value( bool use_absolute_value );
    //bool get_use_absolute_value() const;


    virtual double evaluate_sensor_value();
 
};

}


#endif 
