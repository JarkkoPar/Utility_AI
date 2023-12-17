#ifndef UtilityAISTScoreBasedSelector_H_INCLUDED
#define UtilityAISTScoreBasedSelector_H_INCLUDED 

#include "nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAISTScoreBasedSelector : public UtilityAIStateTreeNodes {
    GDCLASS(UtilityAISTScoreBasedSelector, UtilityAIStateTreeNodes)

private:
    
protected:
    static void _bind_methods();

public:
    UtilityAISTScoreBasedSelector();
    ~UtilityAISTScoreBasedSelector();
    
    
    // Getters and setters for attributes.
    

    // Handling functions.

    virtual UtilityAIStateTreeNodes* _tick(Variant user_data, double delta) override;

    // Godot virtuals.
    void _ready();
};

}


#endif 
