#ifndef UtilityAIBTSequence_H_INCLUDED
#define UtilityAIBTSequence_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTSequence : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTSequence, UtilityAIBehaviourTreeNodes )

private:
    
    int _current_child_index;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTSequence();
    ~UtilityAIBTSequence();
    
    
    // Getters and setters for attributes.
    

    // Handling functions.

    virtual int tick() override;
};

}


#endif 
