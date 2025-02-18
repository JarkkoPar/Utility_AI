#ifndef UtilityAIAngleToVector3SearchCriterion_H_INCLUDED
#define UtilityAIAngleToVector3SearchCriterion_H_INCLUDED

#include "nqs.h"

namespace godot {

class UtilityAIAngleToVector3SearchCriterion : public UtilityAINQSSearchCriteria {
	GDCLASS(UtilityAIAngleToVector3SearchCriterion, UtilityAINQSSearchCriteria)

private:
	float _min_angle_degrees;
	float _max_angle_degrees;

	float _min_angle_radians;
	float _max_angle_radians;

	float _span_radians;
	float _one_over_span_radians;

	Vector3 _angle_to_direction_vector;

protected:
	static void _bind_methods();
	virtual void _initialize_criterion() override;

public:
	UtilityAIAngleToVector3SearchCriterion();
	~UtilityAIAngleToVector3SearchCriterion();

	// Getters and setters for attributes.

	void set_angle_to_direction_vector(Vector3 angle_to_direction_vector);
	Vector3 get_angle_to_direction_vector() const;

	void set_min_angle_degrees(float min_angle_degrees);
	float get_min_angle_degrees() const;

	void set_max_angle_degrees(float max_angle_degrees);
	float get_max_angle_degrees() const;

	// Handling methods.

	virtual void apply_criterion(Node *node, bool &filter_out, float &score) override;
};

} //namespace godot

#endif
