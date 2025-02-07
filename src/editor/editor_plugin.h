#ifndef UTILITY_AI_EDITOR_PLUGIN_H_INCLUDED
#define UTILITY_AI_EDITOR_PLUGIN_H_INCLUDED

#ifdef DEBUG_ENABLED

#include "../behaviour_tree/nodes.h"
#include "../debugger/debugger_plugin.h"
#include <godot_cpp/classes/editor_inspector.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/editor_selection.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/tree.hpp>
#include <godot_cpp/classes/tree_item.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

class UtilityAIEditorPlugin : public EditorPlugin {
	GDCLASS(UtilityAIEditorPlugin, EditorPlugin)

private:
	Node *_editor_scene;
	EditorInterface *_editor_interface;
	EditorSelection *_editor_selection;

	// UI nodes.
	Tree *_node_tree;

	// Debugger.
	Ref<UtilityAIDebuggerPlugin> _debugger;
	Ref<EditorDebuggerSession> _debugger_session;

protected:
	static void _bind_methods();

	void btree_add_child_nodes(Tree *tree, TreeItem *parent_node, UtilityAIBehaviourTreeNodes *parent_ai_node);

public:
	UtilityAIEditorPlugin();
	~UtilityAIEditorPlugin();

	// Godot virtuals.
	//void _enter_tree() override;
	//void _exit_tree() override;
	bool _has_main_screen() const override { return true; };
	void _make_visible(bool visible) override {};
	String _get_plugin_name() const override { return String("Utility AI Editor"); };
	void _notification(int p_what); // override;

	// Signal handlers.

	void _on_selection_changed();

	// Getters and setters for attributes.
	// todo: code
};

} //namespace godot

#endif //debug enabled

#endif