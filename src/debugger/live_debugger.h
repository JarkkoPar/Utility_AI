#ifndef UTILITYAI_LIVE_DEBUGGER_H_INCLUDED
#define UTILITYAI_LIVE_DEBUGGER_H_INCLUDED

#ifdef DEBUG_ENABLED


#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/control.hpp>


namespace godot {

class UtilityAILiveDebugger : public Node {
    GDCLASS(UtilityAILiveDebugger, Node)

private:
    std::vector<ObjectID>   _behaviour_trees;
    std::vector<ObjectID>   _state_trees;
    std::vector<ObjectID>   _agents;
    
    static UtilityAILiveDebugger* _singleton;

    Control*                _live_debugger_scene;
    int                     _current_type_selection;
protected:
    static void _bind_methods();


public:
    UtilityAILiveDebugger();
    ~UtilityAILiveDebugger();

    static UtilityAILiveDebugger* get_singleton();
    
    // Godot virtuals.

    //void _notification( int p_what ) override;


    // Handling methods.
    void register_behaviour_tree(uint64_t instance_id);
    void register_state_tree(uint64_t instance_id);
    void register_ai_agent(uint64_t instance_id);

    void add_as_child_of( Node* debugger_parent_node );

    // UI handling methods.
    void on_type_item_selected(int item);

};

}

#endif //debug enabled
#endif
