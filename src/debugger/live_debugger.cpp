#ifdef DEBUG_ENABLED
#include "live_debugger.h"
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/option_button.hpp>

#include "../behaviour_tree/root.h"
#include "../state_tree/root.h"
#include "../agent_behaviours/agent.h"

using namespace godot;

UtilityAILiveDebugger* UtilityAILiveDebugger::_singleton = nullptr;

UtilityAILiveDebugger* UtilityAILiveDebugger::get_singleton() {
    return _singleton;
}


UtilityAILiveDebugger::UtilityAILiveDebugger() {
    _singleton = this;
    _live_debugger_scene = nullptr;
    _current_type_selection = -1;
}

UtilityAILiveDebugger::~UtilityAILiveDebugger() {
    _singleton = nullptr;
}


void UtilityAILiveDebugger::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add_as_child_of", "debugger_parent_node"), &UtilityAILiveDebugger::add_as_child_of);

    // UI Handling methods.
    ClassDB::bind_method(D_METHOD("on_type_item_selected", "item"), &UtilityAILiveDebugger::on_type_item_selected);
}


void UtilityAILiveDebugger::register_behaviour_tree(uint64_t instance_id) {
    ObjectID new_objectID = ObjectID();
    new_objectID = instance_id;
    _behaviour_trees.push_back(new_objectID);
    WARN_PRINT("Added BTRee");
}

void UtilityAILiveDebugger::register_state_tree(uint64_t instance_id) {
    ObjectID new_objectID = ObjectID();
    new_objectID = instance_id;
    _state_trees.push_back(new_objectID);
    WARN_PRINT("Added State Tree");
}

void UtilityAILiveDebugger::register_ai_agent(uint64_t instance_id) {
    ObjectID new_objectID = ObjectID();
    new_objectID = instance_id;
    _agents.push_back(new_objectID);
    WARN_PRINT("Added AIAgent");
}



void UtilityAILiveDebugger::add_as_child_of( Node* debugger_parent_node ) {
    if( debugger_parent_node == nullptr ) {
        WARN_PRINT("parent is null");
        return;
    }
    if( _live_debugger_scene == nullptr ) {
        Ref<PackedScene> scene_template = godot::ResourceLoader::get_singleton()->load("res://addons/utility_ai/debugger/tree_debugger.tscn");
        _live_debugger_scene = godot::Object::cast_to<Control>(scene_template->instantiate());
        
    }//endif live debugger scene is not loaded.
    
    debugger_parent_node->add_child(_live_debugger_scene);
    
    // Connect the signals.
    OptionButton* select_type = _live_debugger_scene->get_node<OptionButton>("SelectType");
    if( select_type == nullptr ) {
        WARN_PRINT("select type is null");
        return;
    }
    select_type->connect("item_selected", Callable(this, "on_type_item_selected"));
    WARN_PRINT("ALL DONE!");
}


// UI Handling methods.

void UtilityAILiveDebugger::on_type_item_selected(int item) {
    WARN_PRINT("--0");
    
    if( item == _current_type_selection ) {
        return;
    }
    _current_type_selection = item;
    WARN_PRINT("--1");
    OptionButton* select_root = _live_debugger_scene->get_node<OptionButton>("SelectTree");
    select_root->clear();
    WARN_PRINT("--3");
    //WARN_PRINT(String("Got: ") + String(item));
    switch( item ) {
        case 1: { // Behaviour trees.
            for( int i = 0; i < _behaviour_trees.size(); ++i ) {
                ObjectID helper = ObjectID();
                helper = _behaviour_trees[i];
                if( !helper.is_valid() ) {
                    continue;
                }
                UtilityAIBTRoot* btroot = godot::Object::cast_to<UtilityAIBTRoot>(ObjectDB::get_instance(_behaviour_trees[i]));
                if( btroot == nullptr ) {
                    continue;
                }

                select_root->add_item(String(btroot->get_owner()->get_name()) + ": " + String(btroot->get_name()) );
            }//endfor
            WARN_PRINT("--4");
        } break;
        case 2: { // State trees.
            for( int i = 0; i < _state_trees.size(); ++i ) {
                ObjectID helper = ObjectID();
                helper = _state_trees[i];
                if( !helper.is_valid() ) {
                    continue;
                }
                UtilityAISTRoot* stroot = godot::Object::cast_to<UtilityAISTRoot>(ObjectDB::get_instance(_state_trees[i]));
                if( stroot == nullptr ) {
                    continue;
                }

                select_root->add_item(String(stroot->get_owner()->get_name()) + ": " + String(stroot->get_name()) );
            }//endfor
            WARN_PRINT("--5");
        } break;
        default: { // Agent behaviours.
            for( int i = 0; i < _agents.size(); ++i ) {
                ObjectID helper = ObjectID();
                helper = _agents[i];
                if( !helper.is_valid() ) {
                    continue;
                }
                UtilityAIAgent* agent = godot::Object::cast_to<UtilityAIAgent>(ObjectDB::get_instance(_agents[i]));
                if( agent == nullptr ) {
                    continue;
                }

                select_root->add_item(String(agent->get_owner()->get_name()) + ": " + String(agent->get_name()) );
            }//endfor
            WARN_PRINT("--6");
        } break;
    }

    WARN_PRINT("--7");
}



#endif

