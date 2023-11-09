#ifndef UtilityAIPositionQuery_H_INCLUDED
#define UtilityAIPositionQuery_H_INCLUDED 

#include "UtilityAI.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIPositionQuery : public UtilityAI {
    GDCLASS(UtilityAIPositionQuery, UtilityAI)

private:
    

protected:
    static void _bind_methods();

public:
    UtilityAIPositionQuery();
    ~UtilityAIPositionQuery();
    
    
    // Getters and setters for attributes.
    
    
};

}


#endif 
