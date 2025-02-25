#ifndef UtilityAIBTCooldownMsec_H_INCLUDED
#define UtilityAIBTCooldownMsec_H_INCLUDED

#include "decorator_nodes.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIBTCooldownMsec : public UtilityAIBTDecoratorNodes {
	GDCLASS(UtilityAIBTCooldownMsec, UtilityAIBTDecoratorNodes)

private:
	uint64_t _cooldown_msec;
	uint64_t _cooldown_start_timestamp;

	int _cooldown_return_value;
	bool _is_in_cooldown;

protected:
	static void _bind_methods();

public:
	UtilityAIBTCooldownMsec();
	~UtilityAIBTCooldownMsec();

	// Getters and setters for attributes.

	void set_cooldown_msec(int cooldown_msec);
	int get_cooldown_msec() const;

	void set_cooldown_start_timestamp(int cooldown_msec);
	int get_cooldown_start_timestamp() const;

	void set_cooldown_return_value(int cooldown_return_value);
	int get_cooldown_return_value() const;

	// Handling functions.

	virtual int tick(Variant user_data, float delta) override;
};

} //namespace godot

#endif
