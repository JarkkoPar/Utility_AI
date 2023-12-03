#ifndef UtilityAIBTNodeReference_H_INCLUDED
#define UtilityAIBTNodeReference_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTNodeReference : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTNodeReference, UtilityAIBehaviourTreeNodes)

private:
    
    //int _tick_result;
    ObjectID    _cache;
    NodePath    _node_reference_nodepath;
protected:
    static void _bind_methods();

    void _update_cache();
public:
    UtilityAIBTNodeReference();
    ~UtilityAIBTNodeReference();
    
    
    // Getters and setters for attributes.
    
    void set_node_reference_nodepath(const NodePath &node_reference_nodepath);
	NodePath get_node_reference_nodepath() const;
    //void set_tick_result( int tick_result );
    //int  get_tick_result() const;

    // Handling functions.

    virtual int tick(Variant user_data, double delta) override;

    // Godot virtuals.
    void _enter_tree();
};

}


#endif 
