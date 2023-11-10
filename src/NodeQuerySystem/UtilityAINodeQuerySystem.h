#ifndef UtilityAINodeQuerySystem_H_INCLUDED
#define UtilityAINodeQuerySystem_H_INCLUDED 

#include "UtilityAI.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAINodeQuerySystem : public UtilityAI {
    GDCLASS(UtilityAINodeQuerySystem, UtilityAI)

private:
    //TypedArray<Node> _query_results;
    //int              _top_n_to_find;

protected:
    //static void _bind_methods();

public:
    UtilityAINodeQuerySystem();
    ~UtilityAINodeQuerySystem();

    // Handling methods.

    //void execute_queries();

    // Godot virtuals.
    //void _ready();
    
    
};

}


#endif 
