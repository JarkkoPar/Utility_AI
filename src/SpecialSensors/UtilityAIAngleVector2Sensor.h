#ifndef UTILITYAIANGLEVECTOR2SENSOR_H_INCLUDED
#define UTILITYAIANGLEVECTOR2SENSOR_H_INCLUDED 

#include "../UtilityAISensor.h"


namespace godot {

class UtilityAIAngleVector2Sensor : public UtilityAISensor {
    GDCLASS(UtilityAIAngleVector2Sensor, UtilityAISensor )

private:
    Vector2 _from_vector;
    Vector2 _to_vector;
    double  _angle_radian;
    double  _angle_euler;
    double  _min_angle_radian; 
    double  _min_angle_euler; 
    double  _max_angle_radian; 
    double  _max_angle_euler; 
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

    void set_min_angle_euler( double min_angle_radian );
    double get_min_angle_euler() const;

    void set_max_angle_radian( double max_angle_radian );
    double get_max_angle_radian() const;

    void set_max_angle_euler( double max_angle_radian );
    double get_max_angle_euler() const;

    // Debugging / current values.
    
    void set_angle_radian( double angle_radian );
    double get_angle_radian() const;

    void set_angle_euler( double angle_euler );
    double get_angle_euler() const;

};

}


#endif 
