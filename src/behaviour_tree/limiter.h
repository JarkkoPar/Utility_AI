#ifndef UtilityAIBTLimiter_H_INCLUDED
#define UtilityAIBTLimiter_H_INCLUDED 

#include "decorator_nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTLimiter : public UtilityAIBTDecoratorNodes {
    GDCLASS(UtilityAIBTLimiter, UtilityAIBTDecoratorNodes)

private:
    int            _max_repeat_times;    
    int            _current_repeat_times;
    int            _tick_result;
protected:
    static void _bind_methods();

public:
    UtilityAIBTLimiter();
    ~UtilityAIBTLimiter();
    
    
    // Getters and setters for attributes.
    
    int get_max_repeat_times() const;
    void set_max_repeat_times( int repeat_times );
    //int get_tick_result() const;
    //void set_tick_result( int tick_result );

    // Handling functions.
    virtual void reset_bt_node() override;

    virtual int tick(Variant user_data, double delta) override;
};

}


#endif 
