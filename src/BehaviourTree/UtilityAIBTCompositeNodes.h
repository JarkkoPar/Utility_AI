#ifndef UtilityAIBTCompositeNodes_H_INCLUDED
#define UtilityAIBTCompositeNodes_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTCompositeNodes : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTCompositeNodes, UtilityAIBehaviourTreeNodes)

private:
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTCompositeNodes();
    ~UtilityAIBTCompositeNodes();
    

};

}


#endif 
