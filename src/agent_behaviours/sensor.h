#ifndef UtilityAISensor_H_INCLUDED
#define UtilityAISensor_H_INCLUDED

#include "sensors.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAISensor : public UtilityAISensors {
	GDCLASS(UtilityAISensor, UtilityAISensors)

private:
protected:
	static void _bind_methods();

public:
	UtilityAISensor();
	~UtilityAISensor();

	// Handling functions.

	virtual float evaluate_sensor_value() override;

	// Getters and setters for attributes.
};

} //namespace godot

#endif
