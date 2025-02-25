#ifndef UTILITYAIANGLEVECTOR3SENSOR_H_INCLUDED
#define UTILITYAIANGLEVECTOR3SENSOR_H_INCLUDED

#include "../sensor.h"

namespace godot {

class UtilityAIAngleVector3Sensor : public UtilityAISensor {
	GDCLASS(UtilityAIAngleVector3Sensor, UtilityAISensor)

private:
	Vector3 _from_vector;
	Vector3 _to_vector;
	float _angle_radian;
	float _angle_degrees;
	float _max_angle_radian;
	float _max_angle_degrees;
	float _one_over_max_angle_radian;

protected:
	static void _bind_methods();

public:
	UtilityAIAngleVector3Sensor();
	~UtilityAIAngleVector3Sensor();

	// Handling functions.

	virtual float evaluate_sensor_value() override;

	// Getters and setters for attributes.

	// Configuration values.

	void set_to_vector3(Vector3 to);
	Vector3 get_to_vector3() const;

	void set_from_vector3(Vector3 from);
	Vector3 get_from_vector3() const;

	void set_max_angle_radian(float max_angle_radian);
	float get_max_angle_radian() const;

	void set_max_angle_degrees(float max_angle_radian);
	float get_max_angle_degrees() const;

	// Debugging / current values.

	void set_angle_radian(float angle_radian);
	float get_angle_radian() const;

	void set_angle_degrees(float angle_degrees);
	float get_angle_degrees() const;
};

} //namespace godot

#endif
