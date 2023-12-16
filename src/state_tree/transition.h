#ifndef UtilityAIBTRoot_H_INCLUDED
#define UtilityAIBTRoot_H_INCLUDED 

#include "nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAISTTransition : public UtilityAIStateTreeNodes {
    GDCLASS(UtilityAISTTransition, UtilityAIStateTreeNodes)

private:
    UtilityAIStateTreeNodes* _target_state;
protected:
    static void _bind_methods();

public:
    UtilityAISTTransition();
    ~UtilityAISTTransition();
    
    
    // Getters and setters for attributes.

    void set_target_state( UtilityAIStateTreeNodes* target_state );
    UtilityAIStateTreeNodes* get_target_state() const;

    // Handling functions.

    virtual UtilityAIStateTreeNodes* tick(Variant user_data, double delta) override;

    // Godot virtuals.
    void _ready();
};

}


#endif 
