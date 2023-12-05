#ifndef UtilityAIBTRepeatUntil_H_INCLUDED
#define UtilityAIBTRepeatUntil_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTRepeatUntil : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTRepeatUntil, UtilityAIBehaviourTreeNodes)

private:
    int            _max_repeat_times;    
    int            _current_max_repeat_times;
    int            _expected_tick_result;
protected:
    static void _bind_methods();

public:
    UtilityAIBTRepeatUntil();
    ~UtilityAIBTRepeatUntil();
    
    
    // Getters and setters for attributes.
    
    int get_max_repeat_times() const;
    void set_max_repeat_times( int max_repeat_times );
    int get_expected_tick_result() const;
    void set_expected_tick_result( int expected_tick_result );

    // Handling functions.

    virtual int tick(Variant user_data, double delta) override;
};

}


#endif 
