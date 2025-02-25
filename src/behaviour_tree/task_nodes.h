#ifndef UtilityAIBTTaskNodes_H_INCLUDED
#define UtilityAIBTTaskNodes_H_INCLUDED

#include "nodes.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAIBTTaskNodes : public UtilityAIBehaviourTreeNodes {
	GDCLASS(UtilityAIBTTaskNodes, UtilityAIBehaviourTreeNodes)

private:
protected:
	static void _bind_methods();

public:
	UtilityAIBTTaskNodes();
	~UtilityAIBTTaskNodes();
};

} //namespace godot

#endif
