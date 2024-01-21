#ifndef UtilityAIBTSequence_H_INCLUDED
#define UtilityAIBTSequence_H_INCLUDED 

#include "composite_nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTSequence : public UtilityAIBTCompositeNodes {
    GDCLASS(UtilityAIBTSequence, UtilityAIBTCompositeNodes )

private:
    int _current_child_index;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTSequence();
    ~UtilityAIBTSequence();
    
    
    // Handling functions.

    virtual void reset_bt_node() override;

    virtual int tick(Variant user_data, float delta) override;
};

}


#endif 
