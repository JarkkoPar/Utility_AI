#ifndef UtilityAINodeGroupSearchSpace_H_INCLUDED
#define UtilityAINodeGroupSearchSpace_H_INCLUDED

#include "nqs.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAINodeGroupSearchSpace : public UtilityAINQSSearchSpaces {
	GDCLASS(UtilityAINodeGroupSearchSpace, UtilityAINQSSearchSpaces)

private:
	StringName _group_name;

protected:
	static void _bind_methods();

public:
	UtilityAINodeGroupSearchSpace();
	~UtilityAINodeGroupSearchSpace();

	// Getters and setters for attributes.
	void set_group_name(StringName group_name);
	StringName get_group_name() const;

	virtual TypedArray<Node> get_searchspace_nodes() const override;
};

} //namespace godot

#endif
