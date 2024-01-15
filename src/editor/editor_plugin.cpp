#ifdef DEBUG_ENABLED


#include "editor_plugin.h"

//#include "../behaviour_tree/nodes.h"
#include "../behaviour_tree/root.h"

using namespace godot;


UtilityAIEditorPlugin::UtilityAIEditorPlugin() {
    //_editor_scene = nullptr;
    _editor_interface = nullptr;
}


UtilityAIEditorPlugin::~UtilityAIEditorPlugin() {
    
}


void UtilityAIEditorPlugin::_bind_methods() {
    ClassDB::bind_method(D_METHOD("on_selection_changed"), &UtilityAIEditorPlugin::_on_selection_changed);
}

// Godot virtuals.

/**
void UtilityAIEditorPlugin::_enter_tree() {
    
}


void UtilityAIEditorPlugin::_exit_tree() {

}
/**/


void UtilityAIEditorPlugin::_notification(int p_what) {
    switch( p_what ) {
        case NOTIFICATION_ENTER_TREE: {
            _editor_interface = get_editor_interface();
            
            // todo: error handling
            _editor_selection = _editor_interface->get_selection();
            _editor_selection->connect("selection_changed",Callable(this, "on_selection_changed"));
            
            // todo: error handling

            // Load the editor scene. We'll update it through C++, so it is really
            // an empty shell that contains just the UI.
            Ref<PackedScene> scene_template = godot::ResourceLoader::get_singleton()->load("res://addons/utility_ai/editor/editor.tscn");
            _editor_scene = scene_template->instantiate();

            // Set the tree instance pointer.
            _node_tree = _editor_scene->get_node<Tree>("NodeStructure");
            if( _node_tree != nullptr ) {
                WARN_PRINT("gOT TREE!!!");
            }
            //ERR_FAIL_V_MSG( _editor_scene == nullptr, "UtilityAIEditorPlugin::_enter_tree() - Failed to create the editor interface.");
            //godot::EditorInterface::get_editor_main_screen()->add_child(_editor_scene);
            _editor_interface->get_editor_main_screen()->add_child(_editor_scene);

            // Add the debugger.
            _debugger = Ref<UtilityAIDebuggerPlugin>(memnew(UtilityAIDebuggerPlugin));
            add_debugger_plugin(_debugger);
            
            // Add the debugger session.
            //_debugger_session = Ref<EditorDebuggerSession>(_debugger->)
            _debugger_session = _debugger->get_debugger_session();
        }
        break;
        case NOTIFICATION_EXIT_TREE: {

        }
        break;
        
        default: {} break;
    }
}



// Signal handlers.

void UtilityAIEditorPlugin::_on_selection_changed() {
    //WARN_PRINT("SELECTION CHANGED!!!");
    TypedArray<Node> nodes = _editor_selection->get_selected_nodes();
    _node_tree->clear();
    TreeItem* root_item = _node_tree->create_item();
    for( int i = 0; i < nodes.size(); ++i ) {
        if( UtilityAIBTRoot* btroot = godot::Object::cast_to<UtilityAIBTRoot>(nodes[i]) ) {
            root_item->set_text(0, btroot->get_name());
            btree_add_child_nodes( _node_tree, root_item, btroot );
            // Add all the child nodes of the root.
            //TreeItem new_item;
            //new_item.set_text(btnode->get_name());
            //_node_tree->get_tree_i
            //TreeItem* new_item = _node_tree->create_item(root_item);
            //new_item->set_text(0, btroot->get_name());
            return; // DONE!
        }
         
    }

}


void  UtilityAIEditorPlugin::btree_add_child_nodes( Tree* tree, TreeItem* parent_node, UtilityAIBehaviourTreeNodes* parent_ai_node ) {
    if( parent_ai_node == nullptr || parent_node == nullptr ) {
        return;
    }
    
    for( int i = 0; i < parent_ai_node->get_child_count(); ++i ) {
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(parent_ai_node->get_child(i)) ) {
            TreeItem* child_item = tree->create_item(parent_node);
            if( child_item == nullptr ) return;
            child_item->set_text(0, btnode->get_name());
            btree_add_child_nodes(tree, child_item, btnode );
        }
    }//endfor child nodes.
}

#endif //debug enabled

