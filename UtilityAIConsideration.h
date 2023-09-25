#ifndef UtilityAIConsideration_H_INCLUDED
#define UtilityAIConsideration_H_INCLUDED 

#include "UtilityAIConsiderations.h"

#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIConsideration : public UtilityAIConsiderations {
    GDCLASS(UtilityAIConsideration, UtilityAIConsiderations )

private:

    
protected:
    static void _bind_methods();

public:
    UtilityAIConsideration();
    ~UtilityAIConsideration();
    
    
    // Getters and setters for attributes.
    /**
    
   
        
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */

    // Handling functions.

    virtual float evaluate(UtilityAIAgent* agent, double delta) override;
};

}


#endif 
