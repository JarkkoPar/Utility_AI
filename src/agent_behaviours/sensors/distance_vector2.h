#ifndef UTILITYAIDISTANCEVECTOR2SENSOR_H_INCLUDED
#define UTILITYAIDISTANCEVECTOR2SENSOR_H_INCLUDED

#include "../sensor.h"

namespace godot {

class UtilityAIDistanceVector2Sensor : public UtilityAISensor {
	GDCLASS(UtilityAIDistanceVector2Sensor, UtilityAISensor)

private:
	Vector2 _from_vector;
	Vector2 _to_vector;
	Vector2 _from_to_vector;
	Vector2 _direction_vector;
	float _distance_squared;
	float _distance;
	float _max_distance_squared;
	float _one_over_max_distance_squared;
	float _max_distance;

	bool _is_distance_calculated;
	bool _is_direction_vector_calculated;

protected:
	static void _bind_methods();

public:
	UtilityAIDistanceVector2Sensor();
	~UtilityAIDistanceVector2Sensor();

	// Handling functions.

	virtual float evaluate_sensor_value() override;

	// Getters and setters for attributes.

	// Configuration values.

	void set_to_Vector2(Vector2 to);
	Vector2 get_to_Vector2() const;

	void set_from_Vector2(Vector2 from);
	Vector2 get_from_Vector2() const;

	void set_max_distance(float max_distance);
	float get_max_distance() const;

	void set_is_distance_calculated(bool is_distance_calculated);
	bool get_is_distance_calculated() const;

	void set_is_direction_vector_calculated(bool is_direction_vector_calculated);
	bool get_is_direction_vector_calculated() const;

	// Debugging / current values.

	void set_from_to_vector2(Vector2 from_to);
	Vector2 get_from_to_vector2() const;

	void set_direction_vector2(Vector2 direction);
	Vector2 get_direction_vector2() const;

	void set_distance(float distance);
	float get_distance() const;

	void set_distance_squared(float distance_squared);
	float get_distance_squared() const;
};

} //namespace godot

#endif
