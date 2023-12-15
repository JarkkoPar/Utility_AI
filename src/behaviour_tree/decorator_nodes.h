#ifndef UtilityAIBTDecoratorNodes_H_INCLUDED
#define UtilityAIBTDecoratorNodes_H_INCLUDED 

#include "nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTDecoratorNodes : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTDecoratorNodes, UtilityAIBehaviourTreeNodes)

private:
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTDecoratorNodes();
    ~UtilityAIBTDecoratorNodes();
    

};

}


#endif 
