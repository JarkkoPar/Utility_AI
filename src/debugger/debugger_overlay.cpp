#ifdef DEBUG_ENABLED
#include "debugger_overlay.h"
#include <godot_cpp/classes/h_slider.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/time.hpp>

#include "../agent_behaviours/agent.h"
#include "../agent_behaviours/behaviour.h"
#include "../agent_behaviours/behaviour_group.h"
#include "../agent_behaviours/consideration.h"
#include "../agent_behaviours/consideration_group.h"
#include "../agent_behaviours/considerations.h"
#include "../agent_behaviours/sensors.h"
#include "../behaviour_tree/root.h"
#include "../state_tree/root.h"

using namespace godot;

UtilityAIDebuggerOverlay *UtilityAIDebuggerOverlay::_singleton = nullptr;

UtilityAIDebuggerOverlay *UtilityAIDebuggerOverlay::get_singleton() {
	return _singleton;
}

UtilityAIDebuggerOverlay::UtilityAIDebuggerOverlay() {
	_singleton = this;
	_debugger_overlay_scene = nullptr;
	_current_type_selection = -1;
	_current_root_selection = -1;
	_current_root_selection_node = nullptr;
	_type_selection = nullptr;
	_root_selection = nullptr;
	_debug_messages = nullptr;
}

UtilityAIDebuggerOverlay::~UtilityAIDebuggerOverlay() {
	_singleton = nullptr;
}

void UtilityAIDebuggerOverlay::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_as_child_of", "debugger_parent_node"), &UtilityAIDebuggerOverlay::add_as_child_of);

	// UI Handling methods.
	ClassDB::bind_method(D_METHOD("on_type_item_selected", "item"), &UtilityAIDebuggerOverlay::on_type_item_selected);
	ClassDB::bind_method(D_METHOD("on_root_item_selected", "item"), &UtilityAIDebuggerOverlay::on_root_item_selected);
	ClassDB::bind_method(D_METHOD("on_exit_tree"), &UtilityAIDebuggerOverlay::on_exit_tree);
	ClassDB::bind_method(D_METHOD("update_ui"), &UtilityAIDebuggerOverlay::update_ui);
}

// Godot virtuals.

//void UtilityAIDebuggerOverlay::_physics_process(double delta ){

//}

// Handling methods.

int UtilityAIDebuggerOverlay::register_behaviour_tree(uint64_t instance_id) {
	ObjectID new_objectID = ObjectID();
	new_objectID = instance_id;
	int index = _behaviour_trees.size();
	_behaviour_trees.push_back(new_objectID);
	return index;
}

int UtilityAIDebuggerOverlay::register_state_tree(uint64_t instance_id) {
	ObjectID new_objectID = ObjectID();
	new_objectID = instance_id;
	int index = _state_trees.size();
	_state_trees.push_back(new_objectID);
	return index;
}

int UtilityAIDebuggerOverlay::register_ai_agent(uint64_t instance_id) {
	ObjectID new_objectID = ObjectID();
	new_objectID = instance_id;
	int index = _agents.size();
	_agents.push_back(new_objectID);
	return index;
}

void UtilityAIDebuggerOverlay::deregister_behaviour_tree(uint64_t index) {
}

void UtilityAIDebuggerOverlay::deregister_state_tree(uint64_t index) {
}

void UtilityAIDebuggerOverlay::deregister_ai_agent(uint64_t index) {
}

void UtilityAIDebuggerOverlay::add_as_child_of(Node *debugger_parent_node) {
	if (debugger_parent_node == nullptr) {
		//WARN_PRINT("parent is null");
		return;
	}
	if (_debugger_overlay_scene == nullptr) {
		Ref<PackedScene> scene_template = godot::ResourceLoader::get_singleton()->load("res://addons/utility_ai/debugger/utility_ai_debugger_overlay.tscn");
		_debugger_overlay_scene = godot::Object::cast_to<Control>(scene_template->instantiate());

	} //endif live debugger scene is not loaded.
	_debug_messages = _debugger_overlay_scene->get_node<RichTextLabel>("HBoxContainer/TextVBoxContainer/DebugTextArea");

	debugger_parent_node->add_child(_debugger_overlay_scene);
	_debugger_overlay_scene->connect("tree_exited", Callable(this, "on_exit_tree"));

	// Connect the signals.
	_type_selection = _debugger_overlay_scene->get_node<OptionButton>("HBoxContainer/VBoxContainer/SelectType");
	if (_type_selection == nullptr) {
		//WARN_PRINT("select type is null");
		return;
	}
	_type_selection->connect("item_selected", Callable(this, "on_type_item_selected"));

	_root_selection = _debugger_overlay_scene->get_node<OptionButton>("HBoxContainer/VBoxContainer/SelectTree");
	if (_root_selection == nullptr) {
		//WARN_PRINT("select root is null");
		return;
	}
	_root_selection->connect("item_selected", Callable(this, "on_root_item_selected"));
	_current_type_selection = -1;
	on_type_item_selected(0);
	//WARN_PRINT("ALL DONE!");
}

// UI Handling methods.

void UtilityAIDebuggerOverlay::on_type_item_selected(int item) {
	//WARN_PRINT("--0");

	if (item == _current_type_selection) {
		return;
	}
	_current_type_selection = item;
	_current_root_selection = -1;
	_current_root_selection_node = nullptr;
	//WARN_PRINT("--1");
	//OptionButton* select_root = _debugger_overlay_scene->get_node<OptionButton>("SelectTree");
	_root_selection->clear();
	_root_selection->add_item("Select a root node");

	//WARN_PRINT("--3");
	//WARN_PRINT(String("Got: ") + String(item));
	switch (item) {
		case 1: { // Agent behaviours.
			for (int i = 0; i < _agents.size(); ++i) {
				ObjectID helper = ObjectID();
				helper = _agents[i];
				if (!helper.is_valid()) {
					continue;
				}
				UtilityAIAgent *agent = godot::Object::cast_to<UtilityAIAgent>(ObjectDB::get_instance(_agents[i]));
				if (agent == nullptr) {
					continue;
				}
				_root_selection->add_item(String(agent->get_owner()->get_name()) + ": " + String(agent->get_name()));
			} //endfor
			//WARN_PRINT("--6");
		} break;
		case 2: { // Behaviour trees.
			for (int i = 0; i < _behaviour_trees.size(); ++i) {
				ObjectID helper = ObjectID();
				helper = _behaviour_trees[i];
				if (!helper.is_valid()) {
					continue;
				}
				UtilityAIBTRoot *btroot = godot::Object::cast_to<UtilityAIBTRoot>(ObjectDB::get_instance(_behaviour_trees[i]));
				if (btroot == nullptr) {
					continue;
				}
				_root_selection->add_item(String(btroot->get_owner()->get_name()) + ": " + String(btroot->get_name()));
			} //endfor
			//WARN_PRINT("--4");
		} break;
		case 3: { // State trees.
			for (int i = 0; i < _state_trees.size(); ++i) {
				ObjectID helper = ObjectID();
				helper = _state_trees[i];
				if (!helper.is_valid()) {
					continue;
				}
				UtilityAISTRoot *stroot = godot::Object::cast_to<UtilityAISTRoot>(ObjectDB::get_instance(_state_trees[i]));
				if (stroot == nullptr) {
					continue;
				}
				_root_selection->add_item(String(stroot->get_owner()->get_name()) + ": " + String(stroot->get_name()));
			} //endfor
			//WARN_PRINT("--5");
		} break;
		default: { // No selection.
		} break;
	}

	//WARN_PRINT("--7");
}

void UtilityAIDebuggerOverlay::on_root_item_selected(int item) {
	if (item == 0 || _root_selection == nullptr || _type_selection == nullptr)
		return;
	_current_root_selection = item - 1; // The 0th item is the "Select a root node" text.
	Tree *tree = _debugger_overlay_scene->get_node<Tree>("SelectedTree");
	if (!tree)
		return;
	tree->clear();
	TreeItem *root_item = tree->create_item();
	if (!root_item)
		return;
	root_item->set_custom_font_size(0, 10);
	root_item->set_custom_font_size(1, 10);
	root_item->set_custom_font_size(2, 10);
	_current_root_selection_node = nullptr;
	switch (_current_type_selection) {
		case 1: { // Agent behaviours.
			UtilityAIAgent *agent = godot::Object::cast_to<UtilityAIAgent>(ObjectDB::get_instance(_agents[_current_root_selection]));
			_current_root_selection_node = agent;
			root_item->set_text(0, agent->get_name());
			tree_add_child_nodes(tree, root_item, agent);
		} break;
		case 2: { // Behaviour trees.
			// todo: * show the Behaviour Tree debugging view
			//       * update the debugging view with the selected behaviour tree data.
			UtilityAIBTRoot *btroot = godot::Object::cast_to<UtilityAIBTRoot>(ObjectDB::get_instance(_behaviour_trees[_current_root_selection]));
			_current_root_selection_node = btroot;
			root_item->set_text(0, btroot->get_name());
			tree_add_child_nodes(tree, root_item, btroot);
		} break;
		case 3: { // State trees.
			UtilityAISTRoot *stroot = godot::Object::cast_to<UtilityAISTRoot>(ObjectDB::get_instance(_state_trees[_current_root_selection]));
			_current_root_selection_node = stroot;
			root_item->set_text(0, stroot->get_name());
			tree_add_child_nodes(tree, root_item, stroot);
		} break;
		default: { // No selection.
		} break;
	} //end switch
	/**/
}

void UtilityAIDebuggerOverlay::on_exit_tree() {
	// The overlay node is exiting the tree, so clear all the pointers.
	_debugger_overlay_scene->disconnect("tree_exited", Callable(this, "on_exit_tree"));
	_debugger_overlay_scene = nullptr;
	_type_selection = nullptr;
	_root_selection = nullptr;
	_debug_messages = nullptr;
	_current_type_selection = -1;
	_current_root_selection = -1;
	_current_root_selection_node = nullptr;

	_agents.clear();
	_behaviour_trees.clear();
	_state_trees.clear();
}

// Handling methods.

void UtilityAIDebuggerOverlay::update_ui() {
	on_root_item_selected(_current_root_selection + 1);
	godot::String msg = godot::String("Agents: ") + godot::String::num_int64(_agents.size()) + godot::String(" ") + godot::String("| BTrees: ") + godot::String::num_int64(_behaviour_trees.size()) + godot::String(" ") + godot::String("| STrees: ") + godot::String::num_int64(_state_trees.size()) + godot::String(".\n") + godot::String(" ") + godot::String::num_int64(_state_trees.size()) + godot::String(".\n");
	if (_current_root_selection_node != nullptr) {
		Node *root_owner = _current_root_selection_node->get_owner();
		if (root_owner != nullptr) {
			msg = msg + godot::String("Currently inspecting: [b][color=green]") + root_owner->get_name() + godot::String("[/color][/b]\n");
		} else {
			msg = msg + godot::String("[b][color=gray]No owner[/color][/b]\n");
		}
	}
	/**
		 switch(_current_type_selection) {
			case 1: { // Behaviour trees.
				// todo: * show the Behaviour Tree debugging view
				//       * update the debugging view with the selected behaviour tree data.
				UtilityAIBTRoot* btroot = godot::Object::cast_to<UtilityAIBTRoot>(ObjectDB::get_instance(_behaviour_trees[_current_root_selection]));



			} break;
			case 2: { // State trees.
				UtilityAISTRoot* stroot = godot::Object::cast_to<UtilityAISTRoot>(ObjectDB::get_instance(_state_trees[_current_root_selection]));


			} break;
			default: { // Agent behaviours.
				UtilityAIAgent* agent = godot::Object::cast_to<UtilityAIAgent>(ObjectDB::get_instance(_agents[_current_root_selection]));


			} break;
		}//end switch
	/**/
	_debug_messages->set_text(msg);
}

void UtilityAIDebuggerOverlay::tree_add_child_nodes(Tree *tree, TreeItem *parent_node, Node *parent_ai_node) {
	if (parent_ai_node == nullptr || parent_node == nullptr) {
		return;
	}
	uint64_t current_timestamp = godot::Time::get_singleton()->get_ticks_usec();

	for (int i = 0; i < parent_ai_node->get_child_count(); ++i) {
		Node *next_ai_node = parent_ai_node->get_child(i);
		if (!next_ai_node)
			continue;

		TreeItem *child_tree_item = tree->create_item(parent_node);
		if (!child_tree_item)
			return;
		/**
		if( UtilityAIConsideration* cons = godot::Object::cast_to<UtilityAIConsideration>(next_node)) {
			HSlider* new_slider = memnew(HSlider);
			if( new_slider == nullptr ) continue;
			new_slider->set_min(0.0f);
			new_slider->set_max(1.0f);
			new_slider->set_value(cons->get_score());
			child_item->set_cell_mode(1, TreeItem::TreeCellMode::CELL_MODE_CUSTOM);
			child_item->set_custom_draw(1, new_slider, "");

		   child_item->set_text(1, "C");
		}
		/**/
		child_tree_item->set_custom_font_size(0, 10);
		child_tree_item->set_custom_font_size(1, 10);
		child_tree_item->set_custom_font_size(2, 10);
		float score = 0.0f;
		uint64_t tick_timestamp = 0;
		uint64_t eval_timestamp = 0;
		if (UtilityAIAgent *agent = godot::Object::cast_to<UtilityAIAgent>(next_ai_node)) {
			tick_timestamp = agent->get_last_evaluated_timestamp(); // Visited gets only updated if signals are used, so use eval instead
			eval_timestamp = agent->get_last_evaluated_timestamp(); // for the Agent Behaviour tick timestamp.
			score = 0.0f;
		} else if (UtilityAIConsideration *cons = godot::Object::cast_to<UtilityAIConsideration>(next_ai_node)) {
			tick_timestamp = cons->get_last_evaluated_timestamp();
			eval_timestamp = cons->get_last_evaluated_timestamp();
			score = cons->get_score();
		} else if (UtilityAIConsiderationGroup *consg = godot::Object::cast_to<UtilityAIConsiderationGroup>(next_ai_node)) {
			tick_timestamp = consg->get_last_evaluated_timestamp();
			eval_timestamp = consg->get_last_evaluated_timestamp();
			score = consg->get_score();
		} else if (UtilityAIBehaviour *beh = godot::Object::cast_to<UtilityAIBehaviour>(next_ai_node)) {
			tick_timestamp = beh->get_last_evaluated_timestamp();
			eval_timestamp = beh->get_last_evaluated_timestamp();
			score = beh->get_score();
		} else if (UtilityAIBehaviourGroup *behg = godot::Object::cast_to<UtilityAIBehaviourGroup>(next_ai_node)) {
			tick_timestamp = behg->get_last_evaluated_timestamp();
			eval_timestamp = behg->get_last_evaluated_timestamp();
			score = behg->get_score();
		} else if (UtilityAIBehaviourTreeNodes *btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(next_ai_node)) {
			tick_timestamp = btnode->get_last_visited_timestamp();
			eval_timestamp = btnode->get_last_evaluated_timestamp();
			score = btnode->get_score();
		} else if (UtilityAIStateTreeNodes *stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(next_ai_node)) {
			tick_timestamp = stnode->get_last_visited_timestamp();
			eval_timestamp = stnode->get_last_evaluated_timestamp();
			score = stnode->get_score();
		}

		child_tree_item->set_text(0, next_ai_node->get_name());
		child_tree_item->set_text(2, String::num((double)score, 2));
		score = 0.7f * score;
		//child_tree_item->set_custom_bg_color(0, Color(score, score, score));

		uint64_t tick_time_diff = current_timestamp - tick_timestamp;
		if (tick_time_diff > 1000000) {
			tick_time_diff = 1000000;
		}
		uint64_t eval_time_diff = current_timestamp - eval_timestamp;
		if (eval_time_diff > 1000000) {
			eval_time_diff = 1000000;
		}
		float tick_color = 1.0f - (float)tick_time_diff * 0.000001f * 0.7f;
		float eval_color = 1.0f - (float)eval_time_diff * 0.000001f * 0.7f;

		child_tree_item->set_custom_color(0, Color(tick_color, tick_color, tick_color));
		child_tree_item->set_custom_color(2, Color(eval_color * 0.8f, eval_color * 0.8f, eval_color));

		//child_tree_item->set_text(2, "n/a");
		tree_add_child_nodes(tree, child_tree_item, next_ai_node);

	} //endfor child nodes.
}

/**
void  UtilityAIDebuggerOverlay::tree_update_child_nodes( Tree* tree, TreeItem* parent_node, Node* parent_ai_node ) {
	if( parent_ai_node == nullptr || parent_node == nullptr ) {
		return;
	}

	for( int i = 0; i < parent_ai_node->get_child_count(); ++i ) {
		Node* next_ai_node = parent_ai_node->get_child(i);
		TreeItem* next_tree_item = parent_node->get_child(i);
		if( !next_ai_node || !next_tree_item) break;


		float score = 0.0f;
		if( UtilityAIConsideration* cons = godot::Object::cast_to<UtilityAIConsideration>(next_ai_node)) {
			score = cons->get_score();
		}else if( UtilityAIConsiderationGroup* consg = godot::Object::cast_to<UtilityAIConsiderationGroup>(next_ai_node)) {
			score = consg->get_score();
		}else if( UtilityAIBehaviour* beh = godot::Object::cast_to<UtilityAIBehaviour>(next_ai_node)) {
			score = beh->get_score();
		}else if( UtilityAIBehaviourGroup* behg = godot::Object::cast_to<UtilityAIBehaviourGroup>(next_ai_node)) {
			score = behg->get_score();
		}else if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(next_ai_node) ) {
			//if( btnode->get_internal_status() == )
			next_tree_item->set_custom_bg_color(0, Color(0.0f, 0.5f, 0.0f), false);

			score = btnode->get_score();
		}else if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(next_ai_node) ) {

			next_tree_item->set_custom_bg_color(0, Color(0.0f, 0.5f, 0.0f), false);

			score = stnode->get_score();
		}
		next_tree_item->set_text(2, String::num(score,2) );

	}//endfor child nodes.
}
/**/

#endif
