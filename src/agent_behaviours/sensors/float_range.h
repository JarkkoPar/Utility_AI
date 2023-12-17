#ifndef UTILITYAIFLOATRANGESENSOR_H_INCLUDED
#define UTILITYAIFLOATRANGESENSOR_H_INCLUDED 

#include "../sensor.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIFloatRangeSensor : public UtilityAISensor {
    GDCLASS(UtilityAIFloatRangeSensor, UtilityAISensor )

private:
    double _range_min_value;
    double _range_max_value;
    double _range_length;
    double _one_over_range_length;
    double _range_value;
protected:
    static void _bind_methods();

public:
    UtilityAIFloatRangeSensor();
    ~UtilityAIFloatRangeSensor();
    
    // Handling functions. 

    virtual double evaluate_sensor_value() override;

    // Getters and setters for attributes.
    
    void   set_range_min_value( double range_min_value );
    double get_range_min_value() const; 

    void   set_range_max_value( double range_max_value );
    double get_range_max_value() const; 

    void   set_range_value( double range_value );
    double get_range_value() const; 

};

}


#endif 
