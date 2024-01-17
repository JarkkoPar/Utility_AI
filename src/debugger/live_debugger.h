#ifndef UTILITYAI_LIVE_DEBUGGER_H_INCLUDED
#define UTILITYAI_LIVE_DEBUGGER_H_INCLUDED

#ifdef DEBUG_ENABLED


#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/option_button.hpp>
#include <godot_cpp/classes/tree.hpp>


namespace godot {

class UtilityAILiveDebugger : public Node {
    GDCLASS(UtilityAILiveDebugger, Node)

private:
    std::vector<ObjectID>   _behaviour_trees;
    std::vector<ObjectID>   _state_trees;
    std::vector<ObjectID>   _agents;
    
    static UtilityAILiveDebugger* _singleton;

    Control*                _live_debugger_scene;
    OptionButton*           _type_selection;
    OptionButton*           _root_selection;

    int                     _current_type_selection;
    int                     _current_root_selection;
protected:
    static void _bind_methods();


public:
    UtilityAILiveDebugger();
    ~UtilityAILiveDebugger();

    static UtilityAILiveDebugger* get_singleton();
    
    // Godot virtuals.

    //void _notification( int p_what ) override;
    //void _physics_process(double delta ) override;
    void  tree_add_child_nodes( Tree* tree, TreeItem* parent_node, Node* parent_ai_node );
    void  tree_update_child_nodes( Tree* tree, TreeItem* parent_node, Node* parent_ai_node );

    // Handling methods.
    void register_behaviour_tree(uint64_t instance_id);
    void register_state_tree(uint64_t instance_id);
    void register_ai_agent(uint64_t instance_id);

    void add_as_child_of( Node* debugger_parent_node );

    // UI handling methods.
    void on_type_item_selected(int item);
    void on_root_item_selected(int item);

    void update_ui();
};

}

#endif //debug enabled
#endif
