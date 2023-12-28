#ifndef UTILITYAIANGLEVECTOR2SENSOR_H_INCLUDED
#define UTILITYAIANGLEVECTOR2SENSOR_H_INCLUDED 

#include "../sensor.h"


namespace godot {

class UtilityAIAngleVector2Sensor : public UtilityAISensor {
    GDCLASS(UtilityAIAngleVector2Sensor, UtilityAISensor )

private:
    Vector2 _from_vector;
    Vector2 _to_vector;
    float  _angle_radian;
    float  _angle_degrees;
    float  _min_angle_radian; 
    float  _min_angle_degrees; 
    float  _max_angle_radian; 
    float  _max_angle_degrees; 
    float  _one_over_2_pi;
    //float  _one_over_min_angle_radian;
    //float  _one_over_max_angle_radian;
protected:
    static void _bind_methods();

public:
    UtilityAIAngleVector2Sensor();
    ~UtilityAIAngleVector2Sensor();
    
    // Handling functions. 

    virtual float evaluate_sensor_value() override;

    // Getters and setters for attributes.
    
    // Configuration values. 

    void set_to_vector2( Vector2 to );
    Vector2 get_to_vector2() const;

    void set_from_vector2( Vector2 from );
    Vector2 get_from_vector2() const;

    void set_min_angle_radian( float min_angle_radian );
    float get_min_angle_radian() const;

    void set_min_angle_degrees( float min_angle_radian );
    float get_min_angle_degrees() const;

    void set_max_angle_radian( float max_angle_radian );
    float get_max_angle_radian() const;

    void set_max_angle_degrees( float max_angle_radian );
    float get_max_angle_degrees() const;

    // Debugging / current values.
    
    void set_angle_radian( float angle_radian );
    float get_angle_radian() const;

    void set_angle_degrees( float angle_degrees );
    float get_angle_degrees() const;

};

}


#endif 
