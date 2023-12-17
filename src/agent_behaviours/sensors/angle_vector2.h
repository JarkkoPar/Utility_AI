#ifndef UTILITYAIANGLEVECTOR2SENSOR_H_INCLUDED
#define UTILITYAIANGLEVECTOR2SENSOR_H_INCLUDED 

#include "../sensor.h"


namespace godot {

class UtilityAIAngleVector2Sensor : public UtilityAISensor {
    GDCLASS(UtilityAIAngleVector2Sensor, UtilityAISensor )

private:
    Vector2 _from_vector;
    Vector2 _to_vector;
    double  _angle_radian;
    double  _angle_degrees;
    double  _min_angle_radian; 
    double  _min_angle_degrees; 
    double  _max_angle_radian; 
    double  _max_angle_degrees; 
    double  _one_over_2_pi;
    //double  _one_over_min_angle_radian;
    //double  _one_over_max_angle_radian;
protected:
    static void _bind_methods();

public:
    UtilityAIAngleVector2Sensor();
    ~UtilityAIAngleVector2Sensor();
    
    // Handling functions. 

    virtual double evaluate_sensor_value() override;

    // Getters and setters for attributes.
    
    // Configuration values. 

    void set_to_vector2( Vector2 to );
    Vector2 get_to_vector2() const;

    void set_from_vector2( Vector2 from );
    Vector2 get_from_vector2() const;

    void set_min_angle_radian( double min_angle_radian );
    double get_min_angle_radian() const;

    void set_min_angle_degrees( double min_angle_radian );
    double get_min_angle_degrees() const;

    void set_max_angle_radian( double max_angle_radian );
    double get_max_angle_radian() const;

    void set_max_angle_degrees( double max_angle_radian );
    double get_max_angle_degrees() const;

    // Debugging / current values.
    
    void set_angle_radian( double angle_radian );
    double get_angle_radian() const;

    void set_angle_degrees( double angle_degrees );
    double get_angle_degrees() const;

};

}


#endif 
