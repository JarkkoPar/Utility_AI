#ifndef UtilityAI_H_INCLUDED
#define UtilityAI_H_INCLUDED

#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAI : public Node {
	GDCLASS(UtilityAI, Node)

private:
	bool _is_active;

protected:
	static void _bind_methods();

public:
	UtilityAI();
	~UtilityAI();

	// Getters and setters for attributes.
	void set_is_active(bool is_active);
	bool get_is_active() const;
};

} //namespace godot

#endif
