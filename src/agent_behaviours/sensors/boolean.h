#ifndef UTILITYAIBOOLEANSENSOR_H_INCLUDED
#define UTILITYAIBOOLEANSENSOR_H_INCLUDED 

#include "../sensor.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBooleanSensor : public UtilityAISensor {
    GDCLASS(UtilityAIBooleanSensor, UtilityAISensor )

private:
    bool _boolean_value;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBooleanSensor();
    ~UtilityAIBooleanSensor();
    
    // Handling functions. 

    virtual double evaluate_sensor_value() override;

    // Getters and setters for attributes.
    
    void set_boolean_value( bool boolean_value );
    bool get_boolean_value() const; 

};

}


#endif 
