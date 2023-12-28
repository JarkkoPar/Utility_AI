#ifndef UtilityAIBTRandomSelector_H_INCLUDED
#define UtilityAIBTRandomSelector_H_INCLUDED 

#include "composite_nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTRandomSelector : public UtilityAIBTCompositeNodes {
    GDCLASS(UtilityAIBTRandomSelector, UtilityAIBTCompositeNodes)

private:
    TypedArray<int> _child_node_order;    
    //bool _is_reactive;
    int _current_child_index;
protected:
    static void _bind_methods();

public:
    UtilityAIBTRandomSelector();
    ~UtilityAIBTRandomSelector();
    
    
    // Getters and setters for attributes.
        
    //void  set_is_reactive( bool is_reactive );
    //bool  get_is_reactive() const;

    // Handling functions.

    virtual void reset_bt_node() override;

    virtual int tick(Variant user_data, float delta) override;
};

}


#endif 
