#ifndef UtilityAIBehaviourTreeNodes_H_INCLUDED
#define UtilityAIBehaviourTreeNodes_H_INCLUDED

#include "../agent_behaviours/considerations.h"
#include "../resources/considerations/consideration_resources.h"
#include "../utility_ai.h"
#include "definitions.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIBehaviourTreeNodes : public UtilityAI {
	GDCLASS(UtilityAIBehaviourTreeNodes, UtilityAI)

private:
	float _score;
	int _evaluation_method;
	bool _invert_score;
	int _tick_result;
	int _internal_status;
	int _reset_rule;
	bool _has_reset_rule_changed;

	TypedArray<UtilityAIConsiderationResources> _considerations;

protected:
	static void _bind_methods();

	//bool   _is_first_tick;
	std::vector<UtilityAIBehaviourTreeNodes *> _child_btnodes;
	unsigned int _num_child_btnodes;
	std::vector<UtilityAIConsiderations *> _child_considerations;
	unsigned int _num_child_considerations;
#ifdef DEBUG_ENABLED
	uint64_t _last_evaluated_timestamp;
	uint64_t _last_visited_timestamp;
#endif
public:
	UtilityAIBehaviourTreeNodes();
	~UtilityAIBehaviourTreeNodes();

	// Getters and setters for attributes.

#ifdef DEBUG_ENABLED
	inline uint64_t get_last_visited_timestamp() const { return _last_visited_timestamp; };
	inline uint64_t get_last_evaluated_timestamp() const { return _last_evaluated_timestamp; };
#endif

	void set_considerations(TypedArray<UtilityAIConsiderationResources> considerations);
	TypedArray<UtilityAIConsiderationResources> get_considerations() const;

	void set_evaluation_method(int evaluation_method);
	int get_evaluation_method() const;

	enum UtilityAIBehaviourTreeNodesEvaluationMethod {
		Sum = 0,
		Min = 1,
		Max = 2,
		Mean = 3,
		Multiply = 4,
		FirstNonZero = 5,
		//OneMinusScore=6
	};

	void set_score(float score);
	float get_score() const;

	void set_tick_result(int tick_result);
	int get_tick_result() const;

	void set_internal_status(int internal_status);
	int get_internal_status() const;

	void set_reset_rule(int reset_rule);
	int get_reset_rule() const;

	enum UtilityAIBehaviourTreeNodesResetRule {
		WHEN_TICKED = 0,
		WHEN_COMPLETED,
		WHEN_TICKED_AFTER_BEING_COMPLETED,
		NEVER,
	};

	// Handling functions.

	virtual float evaluate();

	virtual int tick(Variant user_data, float delta);

	virtual void reset();
	//virtual void reset_for_looping();
	virtual void reset_bt_node() {};
	virtual void update_child_vectors();

	inline virtual bool has_completed() { return (_internal_status == BT_INTERNAL_STATUS_COMPLETED); };

	// Godot virtuals.
	// none.
	virtual void _notification(int p_what);
};

} //namespace godot

#endif
