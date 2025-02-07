#ifndef UtilityAISTSelector_H_INCLUDED
#define UtilityAISTSelector_H_INCLUDED

#include "nodes.h"
//#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAISTNode : public UtilityAIStateTreeNodes {
	GDCLASS(UtilityAISTNode, UtilityAIStateTreeNodes)

private:
protected:
	static void _bind_methods();

public:
	UtilityAISTNode();
	~UtilityAISTNode();
};

} //namespace godot

#endif
