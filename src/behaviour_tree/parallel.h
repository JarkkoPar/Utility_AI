#ifndef UtilityAIBTParallel_H_INCLUDED
#define UtilityAIBTParallel_H_INCLUDED 

#include "composite_nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTParallel : public UtilityAIBTCompositeNodes {
    GDCLASS(UtilityAIBTParallel, UtilityAIBTCompositeNodes )

private:
    //bool _is_reactive;
    int _current_child_index;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTParallel();
    ~UtilityAIBTParallel();
    
    
    // Getters and setters for attributes.
    //void set_is_reactive( bool is_reactive );
    //bool get_is_reactive() const;

    // Handling functions.

    virtual int tick(Variant user_data, float delta) override;
};

}


#endif 
