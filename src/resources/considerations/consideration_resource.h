#ifndef UTILITY_AI_CONSIDERATION_RESOURCE_H_INCLUDED
#define UTILITY_AI_CONSIDERATION_RESOURCE_H_INCLUDED

#include "../../agent_behaviours/sensors.h"
#include "consideration_resources.h"
#include <godot_cpp/classes/curve.hpp>
#include <godot_cpp/classes/resource.hpp>

namespace godot {

class UtilityAIConsiderationResource : public UtilityAIConsiderationResources {
	GDCLASS(UtilityAIConsiderationResource, UtilityAIConsiderationResources)

private:
	bool _is_active;
	Ref<Curve> _activation_curve;
	UtilityAISensors *_input_sensor;
	NodePath _input_sensor_nodepath; // Node pointer doesn't seem to get saved for a resource, so a node path needs to be used.
protected:
	static void _bind_methods();

public:
	UtilityAIConsiderationResource();
	~UtilityAIConsiderationResource();

	// Getters and setters for attributes.

	void set_input_sensor_nodepath(NodePath input_sensor_nodepath);
	NodePath get_input_sensor_nodepath() const;

	void set_activation_curve(Ref<Curve> activation_curve);
	Ref<Curve> get_activation_curve() const;

	// Handling methods.

	virtual float evaluate(bool &has_vetoed, Node *parent_node) override;
	virtual float sample_activation_curve(float input_value) const;
};

} //namespace godot

#endif
