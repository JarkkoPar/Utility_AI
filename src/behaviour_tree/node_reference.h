#ifndef UtilityAIBTNodeReference_H_INCLUDED
#define UtilityAIBTNodeReference_H_INCLUDED 

#include "task_nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTNodeReference : public UtilityAIBTTaskNodes {
    GDCLASS(UtilityAIBTNodeReference, UtilityAIBTTaskNodes)

private:
    
    //int _tick_result;
    UtilityAIBehaviourTreeNodes* _node_reference;
    ObjectID                     _cache;
protected:
    static void _bind_methods();

    void _update_cache();
public:
    UtilityAIBTNodeReference();
    ~UtilityAIBTNodeReference();
    
    
    // Getters and setters for attributes.
    
    void set_node_reference(UtilityAIBehaviourTreeNodes* node_reference);
	UtilityAIBehaviourTreeNodes* get_node_reference() const;
    //void set_tick_result( int tick_result );
    //int  get_tick_result() const;

    // Handling functions.
    virtual void reset() override;
    virtual int tick(Variant user_data, float delta) override;
};

}


#endif 
