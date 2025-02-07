#ifndef UtilityAIBTRepeatUntil_H_INCLUDED
#define UtilityAIBTRepeatUntil_H_INCLUDED

#include "decorator_nodes.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIBTRepeatUntil : public UtilityAIBTDecoratorNodes {
	GDCLASS(UtilityAIBTRepeatUntil, UtilityAIBTDecoratorNodes)

private:
	int _max_repeat_times;
	int _current_max_repeat_times;
	int _expected_tick_result;
	bool _is_expected_tick_result_reached;

protected:
	static void _bind_methods();

public:
	UtilityAIBTRepeatUntil();
	~UtilityAIBTRepeatUntil();

	// Getters and setters for attributes.

	int get_max_repeat_times() const;
	void set_max_repeat_times(int max_repeat_times);
	int get_current_max_repeat_times() const;
	void set_current_max_repeat_times(int current_max_repeat_times);
	int get_expected_tick_result() const;
	void set_expected_tick_result(int expected_tick_result);

	// Handling functions.

	virtual void reset_bt_node() override;

	virtual int tick(Variant user_data, float delta) override;
};

} //namespace godot

#endif
