#ifndef UtilityAIBTLeaf_H_INCLUDED
#define UtilityAIBTLeaf_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTLeaf : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTLeaf, UtilityAIBehaviourTreeNodes)

private:
    
    int _tick_result;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTLeaf();
    ~UtilityAIBTLeaf();
    
    
    // Getters and setters for attributes.
        
    void set_tick_result( int tick_result );
    int  get_tick_result() const;

    // Handling functions.

    virtual int tick() override;
};

}


#endif 
