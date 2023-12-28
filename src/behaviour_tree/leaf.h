#ifndef UtilityAIBTLeaf_H_INCLUDED
#define UtilityAIBTLeaf_H_INCLUDED 

#include "task_nodes.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/method_ptrcall.hpp>


namespace godot {

class UtilityAIBTLeaf : public UtilityAIBTTaskNodes {
    GDCLASS(UtilityAIBTLeaf, UtilityAIBTTaskNodes)

private:
    //Callable _tick_method;
    //int _tick_result;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTLeaf();
    ~UtilityAIBTLeaf();
    
    
    // Getters and setters for attributes.
        
    //void set_tick_result( int tick_result );
    //int  get_tick_result() const;

    // Handling functions.

    virtual int tick(Variant user_data, float delta) override;

    // Godot virtuals.

    //void _enter_tree();

};

}


#endif 
