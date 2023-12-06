#ifndef UtilityAIBTSequence_H_INCLUDED
#define UtilityAIBTSequence_H_INCLUDED 

#include "UtilityAIBTCompositeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTSequence : public UtilityAIBTCompositeNodes {
    GDCLASS(UtilityAIBTSequence, UtilityAIBTCompositeNodes )

private:
    bool _is_reactive;
    int _current_child_index;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTSequence();
    ~UtilityAIBTSequence();
    
    
    // Getters and setters for attributes.
    void set_is_reactive( bool is_reactive );
    bool get_is_reactive() const;

    // Handling functions.

    virtual void reset_bt_node() override;

    virtual int tick(Variant user_data, double delta) override;
};

}


#endif 
