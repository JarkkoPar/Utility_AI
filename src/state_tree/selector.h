#ifndef UtilityAISTSelector_H_INCLUDED
#define UtilityAISTSelector_H_INCLUDED 

#include "nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAISTSelector : public UtilityAIStateTreeNodes {
    GDCLASS(UtilityAISTSelector, UtilityAIStateTreeNodes)

private:
    int _current_child_index;
protected:
    static void _bind_methods();

public:
    UtilityAISTSelector();
    ~UtilityAISTSelector();
    
    
    // Getters and setters for attributes.
    

    // Handling functions.

    virtual UtilityAIStateTreeNodes* tick(Variant user_data, double delta) override;

    // Godot virtuals.
    void _ready();
};

}


#endif 
