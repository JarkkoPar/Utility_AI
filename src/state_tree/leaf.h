#ifndef UtilityAISTLeaf_H_INCLUDED
#define UtilityAISTLeaf_H_INCLUDED 

#include "task_nodes.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/method_ptrcall.hpp>


namespace godot {

class UtilityAISTLeaf : public UtilityAIBTTaskNodes {
    GDCLASS(UtilityAISTLeaf, UtilityAIBTTaskNodes)

private:
    //Callable _tick_method;
    //int _tick_result;
    
protected:
    static void _bind_methods();

public:
    UtilityAISTLeaf();
    ~UtilityAISTLeaf();
    
    
    // Getters and setters for attributes.
        
    //void set_tick_result( int tick_result );
    //int  get_tick_result() const;

    // Handling functions.

    //virtual int _tick(Variant user_data, double delta) override;

    // Godot virtuals.

    //void _enter_tree();

};

}


#endif 
