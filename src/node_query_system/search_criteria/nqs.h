#ifndef UtilityAINQSSearchCriterias_H_INCLUDED
#define UtilityAINQSSearchCriterias_H_INCLUDED
#include "../utility_ai.h"
//#include "node_query_system.h"
//#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/curve.hpp>

namespace godot {

class UtilityAINQSSearchCriteria : public UtilityAI { //NodeQuerySystem {
	GDCLASS(UtilityAINQSSearchCriteria, UtilityAI) //NodeQuerySystem )

private:
	bool _use_for_scoring;
	bool _use_for_filtering;

	Ref<Curve> _activation_curve;

protected:
	static void _bind_methods();

	virtual void _initialize_criterion() {};

	float _score;
	bool _is_filtered;

public:
	UtilityAINQSSearchCriteria();
	~UtilityAINQSSearchCriteria();

	// Godot virtuals.
	void _ready() override;

	// Getters and setters for attributes.

	void set_use_for_scoring(bool use_for_scoring);
	bool get_use_for_scoring() const;

	void set_use_for_filtering(bool use_for_filtering);
	bool get_use_for_filtering() const;

	void set_is_filtered(bool is_filtered);
	bool get_is_filtered() const;

	void set_score(float score);
	float get_score() const;

	void set_activation_curve(Ref<Curve> activation_curve);
	Ref<Curve> get_activation_curve() const;

	// Handling methods.

	virtual void apply_criterion(Node *node, bool &filter_out, float &score);
	virtual float sample_activation_curve(float input_value) const;
};

} //namespace godot

#endif
