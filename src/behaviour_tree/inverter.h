#ifndef UtilityAIBTInverter_H_INCLUDED
#define UtilityAIBTInverter_H_INCLUDED

#include "decorator_nodes.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIBTInverter : public UtilityAIBTDecoratorNodes {
	GDCLASS(UtilityAIBTInverter, UtilityAIBTDecoratorNodes)

private:
	//int _tick_result;

protected:
	static void _bind_methods();

public:
	UtilityAIBTInverter();
	~UtilityAIBTInverter();

	// Getters and setters for attributes.

	//void set_tick_result( int tick_result );
	//int  get_tick_result() const;

	// Handling functions.

	virtual int tick(Variant user_data, float delta) override;
};

} //namespace godot

#endif
