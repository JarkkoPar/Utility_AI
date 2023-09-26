#ifndef UtilityAISensor_H_INCLUDED
#define UtilityAISensor_H_INCLUDED 

#include "UtilityAISensors.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAISensor : public UtilityAISensors {
    GDCLASS(UtilityAISensor, UtilityAISensors )

private:
    
    
protected:
    static void _bind_methods();

public:
    UtilityAISensor();
    ~UtilityAISensor();
    
    // Handling functions. 

    virtual double evaluate_sensor_value() override;

    // Getters and setters for attributes.
    
};

}


#endif 
