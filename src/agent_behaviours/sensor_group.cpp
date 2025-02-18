#include "sensor_group.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// Method binds.

void UtilityAISensorGroup::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAISensorGroup::set_evaluation_method);
	ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAISensorGroup::get_evaluation_method);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method", "get_evaluation_method");

	ClassDB::bind_method(D_METHOD("set_invert_sensor_value", "invert_sensor_value"), &UtilityAISensorGroup::set_invert_sensor_value);
	ClassDB::bind_method(D_METHOD("get_invert_sensor_value"), &UtilityAISensorGroup::get_invert_sensor_value);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "invert_sensor_value", PROPERTY_HINT_NONE), "set_invert_sensor_value", "get_invert_sensor_value");
}

// Constructor and destructor.

UtilityAISensorGroup::UtilityAISensorGroup() {
	_evaluation_method = UtilityAISensorGroupEvaluationMethod::Mean;
	_invert_sensor_value = false;
}

UtilityAISensorGroup::~UtilityAISensorGroup() {
}

// Handling functions.

float UtilityAISensorGroup::evaluate_sensor_value() {
#ifdef DEBUG_ENABLED
	_last_evaluated_timestamp = godot::Time::get_singleton()->get_ticks_usec();
#endif

	if (!get_is_active())
		return 0.0f;
	if (Engine::get_singleton()->is_editor_hint())
		return 0.0f;

	float sensor_value = 0.0f;

	// Evaluate the children.
	int num_children = get_child_count();
	if (num_children < 1)
		return 0.0f;
	float child_sensor_value = 0.0f;
	for (int i = 0; i < num_children; ++i) {
		Node *node = get_child(i);
		if (node == nullptr)
			continue;
		UtilityAISensors *sensorNode = godot::Object::cast_to<UtilityAISensors>(node);
		if (sensorNode == nullptr)
			continue;
		if (!sensorNode->get_is_active())
			continue;
		child_sensor_value = sensorNode->evaluate_sensor_value();

		switch (_evaluation_method) {
			case UtilityAISensorGroupEvaluationMethod::Min: {
				if (i == 0)
					sensor_value = child_sensor_value;
				if (child_sensor_value < sensor_value)
					sensor_value = child_sensor_value;
			} break;
			case UtilityAISensorGroupEvaluationMethod::Max: {
				if (i == 0)
					sensor_value = child_sensor_value;
				if (child_sensor_value > sensor_value)
					sensor_value = child_sensor_value;
			} break;
			case UtilityAISensorGroupEvaluationMethod::Multiply: {
				if (i == 0)
					sensor_value = child_sensor_value;
				else
					sensor_value *= child_sensor_value;
			} break;
			case UtilityAISensorGroupEvaluationMethod::FirstNonZero: {
				if (child_sensor_value > 0.0f) {
					//sensor_value = child_sensor_value;
					if (_invert_sensor_value) {
						sensor_value = 1.0f - child_sensor_value;
					} else {
						sensor_value = child_sensor_value;
					}

					set_sensor_value(sensor_value);
					return sensor_value;
				}
			} break;
			default:
				sensor_value += child_sensor_value;
		} //end switch evaluation method

	} //endfor children

	if (_evaluation_method == UtilityAISensorGroupEvaluationMethod::Mean) {
		sensor_value = sensor_value / ((float)num_children);
	}

	if (_invert_sensor_value) {
		sensor_value = 1.0f - sensor_value;
	}

	set_sensor_value(sensor_value);
	return sensor_value;
}

// Getters and Setters.

void UtilityAISensorGroup::set_evaluation_method(int evaluation_method) {
	_evaluation_method = evaluation_method;
}

int UtilityAISensorGroup::get_evaluation_method() const {
	return _evaluation_method;
}

void UtilityAISensorGroup::set_invert_sensor_value(bool invert_sensor_value) {
	_invert_sensor_value = invert_sensor_value;
}

bool UtilityAISensorGroup::get_invert_sensor_value() const {
	return _invert_sensor_value;
}
