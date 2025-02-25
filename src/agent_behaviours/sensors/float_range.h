#ifndef UTILITYAIFLOATRANGESENSOR_H_INCLUDED
#define UTILITYAIFLOATRANGESENSOR_H_INCLUDED

#include "../sensor.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIFloatRangeSensor : public UtilityAISensor {
	GDCLASS(UtilityAIFloatRangeSensor, UtilityAISensor)

private:
	float _range_min_value;
	float _range_max_value;
	float _range_length;
	float _one_over_range_length;
	float _range_value;

protected:
	static void _bind_methods();

public:
	UtilityAIFloatRangeSensor();
	~UtilityAIFloatRangeSensor();

	// Handling functions.

	virtual float evaluate_sensor_value() override;

	// Getters and setters for attributes.

	void set_range_min_value(float range_min_value);
	float get_range_min_value() const;

	void set_range_max_value(float range_max_value);
	float get_range_max_value() const;

	void set_range_value(float range_value);
	float get_range_value() const;
};

} //namespace godot

#endif
