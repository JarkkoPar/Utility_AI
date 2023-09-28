#ifndef UtilityAIActions_H_INCLUDED
#define UtilityAIActions_H_INCLUDED 

#include "UtilityAI.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIActions : public UtilityAI {
    GDCLASS(UtilityAIActions, UtilityAI)

private:
    
    
    
protected:
    static void _bind_methods();

public:
    UtilityAIActions();
    ~UtilityAIActions();
    
    
    // Getters and setters for attributes.
    
    

 
    /**
    
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */
    
    // Handling functions.

    virtual bool start_action();
};

}


#endif 
