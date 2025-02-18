#ifndef UTILITYAI_DEBUGGER_OVERLAY_H_INCLUDED
#define UTILITYAI_DEBUGGER_OVERLAY_H_INCLUDED

#ifdef DEBUG_ENABLED

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/option_button.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/tree.hpp>

namespace godot {

class UtilityAIDebuggerOverlay : public Node {
	GDCLASS(UtilityAIDebuggerOverlay, Node)

private:
	std::vector<ObjectID> _behaviour_trees;
	std::vector<ObjectID> _state_trees;
	std::vector<ObjectID> _agents;

	static UtilityAIDebuggerOverlay *_singleton;

	Control *_debugger_overlay_scene;
	OptionButton *_type_selection;
	OptionButton *_root_selection;
	RichTextLabel *_debug_messages;

	int _current_type_selection;
	int _current_root_selection;
	Node *_current_root_selection_node;

protected:
	static void _bind_methods();

public:
	UtilityAIDebuggerOverlay();
	~UtilityAIDebuggerOverlay();

	static UtilityAIDebuggerOverlay *get_singleton();

	// Godot virtuals.

	//void _notification( int p_what ) override;
	//void _physics_process(double delta ) override;
	void tree_add_child_nodes(Tree *tree, TreeItem *parent_node, Node *parent_ai_node);
	//void  tree_update_child_nodes( Tree* tree, TreeItem* parent_node, Node* parent_ai_node );

	// Handling methods.
	int register_behaviour_tree(uint64_t instance_id);
	int register_state_tree(uint64_t instance_id);
	int register_ai_agent(uint64_t instance_id);

	void deregister_behaviour_tree(uint64_t instance_id);
	void deregister_state_tree(uint64_t instance_id);
	void deregister_ai_agent(uint64_t instance_id);

	void add_as_child_of(Node *debugger_parent_node);

	// UI handling methods.
	void on_type_item_selected(int item);
	void on_root_item_selected(int item);
	void on_exit_tree();

	void update_ui();
};

} //namespace godot

#endif //debug enabled
#endif
