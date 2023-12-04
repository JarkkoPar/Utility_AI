#ifndef UtilityAIBTPassThrough_H_INCLUDED
#define UtilityAIBTPassThrough_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/method_ptrcall.hpp>


namespace godot {

class UtilityAIBTPassThrough : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTPassThrough, UtilityAIBehaviourTreeNodes)

private:
    int _tick_result;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTPassThrough();
    ~UtilityAIBTPassThrough();
    
    
    // Getters and setters for attributes.
        
    void set_tick_result( int tick_result );
    int  get_tick_result() const;

    // Handling functions.

    virtual int tick(Variant user_data, double delta) override;

    // Godot virtuals.

};

}


#endif 
