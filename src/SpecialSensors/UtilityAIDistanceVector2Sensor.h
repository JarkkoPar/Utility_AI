#ifndef UTILITYAIDISTANCEVECTOR2SENSOR_H_INCLUDED
#define UTILITYAIDISTANCEVECTOR2SENSOR_H_INCLUDED 

#include "../UtilityAISensor.h"


namespace godot {

class UtilityAIDistanceVector2Sensor : public UtilityAISensor {
    GDCLASS(UtilityAIDistanceVector2Sensor, UtilityAISensor )

private:
    Vector2 _from_vector;
    Vector2 _to_vector;
    Vector2 _from_to_vector;
    Vector2 _direction_vector;
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
    UtilityAIDistanceVector2Sensor();
    ~UtilityAIDistanceVector2Sensor();
    
    // Handling functions. 

    virtual double evaluate_sensor_value() override;

    // Getters and setters for attributes.
    
    // Configuration values. 

    void set_to_Vector2( Vector2 to );
    Vector2 get_to_Vector2() const;

    void set_from_Vector2( Vector2 from );
    Vector2 get_from_Vector2() const;

    void set_max_distance( double max_distance );
    double get_max_distance() const;

    void set_is_distance_calculated( bool is_distance_calculated );
    bool get_is_distance_calculated() const;

    void set_is_direction_vector_calculated( bool is_direction_vector_calculated );
    bool get_is_direction_vector_calculated() const;

    // Debugging / current values.

    void set_from_to_vector2( Vector2 from_to );
    Vector2 get_from_to_vector2() const;

    void set_direction_vector2( Vector2 direction );
    Vector2 get_direction_vector2() const;
    
    void set_distance( double distance );
    double get_distance() const;
    
    void set_distance_squared( double distance_squared );
    double get_distance_squared() const;

};

}


#endif 
