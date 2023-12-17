#ifndef UTILITYAIANGLEVECTOR3SENSOR_H_INCLUDED
#define UTILITYAIANGLEVECTOR3SENSOR_H_INCLUDED 

#include "../sensor.h"


namespace godot {

class UtilityAIAngleVector3Sensor : public UtilityAISensor {
    GDCLASS(UtilityAIAngleVector3Sensor, UtilityAISensor )

private:
    Vector3 _from_vector;
    Vector3 _to_vector;
    double  _angle_radian;
    double  _angle_degrees;
    double  _max_angle_radian; 
    double  _max_angle_degrees; 
    double  _one_over_max_angle_radian;

protected:
    static void _bind_methods();

public:
    UtilityAIAngleVector3Sensor();
    ~UtilityAIAngleVector3Sensor();
    
    // Handling functions. 

    virtual double evaluate_sensor_value() override;

    // Getters and setters for attributes.
    
    // Configuration values. 

    void set_to_vector3( Vector3 to );
    Vector3 get_to_vector3() const;

    void set_from_vector3( Vector3 from );
    Vector3 get_from_vector3() const;

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
