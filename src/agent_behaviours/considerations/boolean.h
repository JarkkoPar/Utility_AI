#ifndef UtilityAIBooleanConsideration_H_INCLUDED
#define UtilityAIBooleanConsideration_H_INCLUDED

#include "../consideration.h"

namespace godot {

class UtilityAIBooleanConsideration : public UtilityAIConsideration {
	GDCLASS(UtilityAIBooleanConsideration, UtilityAIConsideration)

private:
	float _true_score_value;
	float _false_score_value;

protected:
	static void _bind_methods();

	virtual void _evaluate_consideration() override;

public:
	UtilityAIBooleanConsideration();
	~UtilityAIBooleanConsideration();

	// Getters and setters for attributes.

	void set_true_score_value(float true_score_value);
	float get_true_score_value() const;

	void set_false_score_value(float false_score_value);
	float get_false_score_value() const;

	// Godot virtuals.
	//void _ready();
	//void _notification( int p_what );

	// Handling functions.

	virtual float sample_activation_curve(float input_value) const override;
};

} //namespace godot

#endif
