#ifndef UtilityAISensorGroup_H_INCLUDED
#define UtilityAISensorGroup_H_INCLUDED

#include "sensors.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAISensorGroup : public UtilityAISensors {
	GDCLASS(UtilityAISensorGroup, UtilityAISensors)

private:
	int _evaluation_method;
	bool _invert_sensor_value;

protected:
	static void _bind_methods();

public:
	UtilityAISensorGroup();
	~UtilityAISensorGroup();

	// Getters and setters for attributes.

	void set_evaluation_method(int evaluation_method);
	int get_evaluation_method() const;

	enum UtilityAISensorGroupEvaluationMethod {
		Sum = 0,
		Min = 1,
		Max = 2,
		Mean = 3,
		Multiply = 4,
		FirstNonZero = 5,
	};

	void set_invert_sensor_value(bool invert_sensor_value);
	bool get_invert_sensor_value() const;

	// Handling functions.

	virtual float evaluate_sensor_value() override;
};

} //namespace godot

#endif
