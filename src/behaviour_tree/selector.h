#ifndef UtilityAIBTSelector_H_INCLUDED
#define UtilityAIBTSelector_H_INCLUDED

#include "composite_nodes.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIBTSelector : public UtilityAIBTCompositeNodes {
	GDCLASS(UtilityAIBTSelector, UtilityAIBTCompositeNodes)

private:
	int _current_child_index;

protected:
	static void _bind_methods();

public:
	UtilityAIBTSelector();
	~UtilityAIBTSelector();

	// Handling functions.
	virtual void reset_bt_node() override;

	virtual int tick(Variant user_data, float delta) override;
};

} //namespace godot

#endif
