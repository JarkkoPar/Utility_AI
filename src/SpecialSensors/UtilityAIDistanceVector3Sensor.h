#ifndef UTILITYAIDISTANCEVECTOR3SENSOR_H_INCLUDED
#define UTILITYAIDISTANCEVECTOR3SENSOR_H_INCLUDED 

#include "../UtilityAISensor.h"


namespace godot {

class UtilityAIDistanceVector3Sensor : public UtilityAISensor {
    GDCLASS(UtilityAIDistanceVector3Sensor, UtilityAISensor )

private:
    Vector3 _from_vector;
    Vector3 _to_vector;
    Vector3 _from_to_vector;
    Vector3 _direction_vector;
    double  _distance_squared;
    double  _distance;
    double  _max_distance_squared;
    double  _one_over_max_distance_squared;
    double  _max_distance; 

    bool    _is_distance_calculated;
    bool    _is_direction_vector_calculated;
protected:
    static void _bind_methods();

public:
    UtilityAIDistanceVector3Sensor();
    ~UtilityAIDistanceVector3Sensor();
    
    // Handling functions. 

    virtual double evaluate_sensor_value() override;

    // Getters and setters for attributes.
    
    // Configuration values. 

    void set_to_vector3( Vector3 to );
    Vector3 get_to_vector3() const;

    void set_from_vector3( Vector3 from );
    Vector3 get_from_vector3() const;

    void set_max_distance( double max_distance );
    double get_max_distance() const;

    void set_is_distance_calculated( bool is_distance_calculated );
    bool get_is_distance_calculated() const;

    void set_is_direction_vector_calculated( bool is_direction_vector_calculated );
    bool get_is_direction_vector_calculated() const;

    // Debugging / current values.

    void set_from_to_vector3( Vector3 from_to );
    Vector3 get_from_to_vector3() const;

    void set_direction_vector3( Vector3 direction );
    Vector3 get_direction_vector3() const;
    
    void set_distance( double distance );
    double get_distance() const;
    
    void set_distance_squared( double distance_squared );
    double get_distance_squared() const;

};

}


#endif 
