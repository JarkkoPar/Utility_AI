#ifndef UtilityAIBTPassThrough_H_INCLUDED
#define UtilityAIBTPassThrough_H_INCLUDED 

#include "decorator_nodes.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/method_ptrcall.hpp>


namespace godot {

class UtilityAIBTPassThrough : public UtilityAIBTDecoratorNodes {
    GDCLASS(UtilityAIBTPassThrough, UtilityAIBTDecoratorNodes)

private:
    int _tick_result;
    bool _has_on_tick_method;
    bool _has_tick_method;
protected:
    static void _bind_methods();

public:
    UtilityAIBTPassThrough();
    ~UtilityAIBTPassThrough();
    
    
    // Getters and setters for attributes.
        
    void set_tick_result( int tick_result );
    int  get_tick_result() const;

    // Handling functions.

    virtual int tick(Variant user_data, float delta) override;

    // Godot virtuals.
    void _notification( int p_what ) override;
};

}


#endif 
