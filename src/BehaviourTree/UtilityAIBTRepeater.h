#ifndef UtilityAIBTRepeater_H_INCLUDED
#define UtilityAIBTRepeater_H_INCLUDED 

#include "UtilityAIBTDecoratorNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTRepeater : public UtilityAIBTDecoratorNodes {
    GDCLASS(UtilityAIBTRepeater, UtilityAIBTDecoratorNodes)

private:
    int            _repeat_times;    
    int            _current_repeat_times;
    int            _tick_result;
protected:
    static void _bind_methods();

public:
    UtilityAIBTRepeater();
    ~UtilityAIBTRepeater();
    
    
    // Getters and setters for attributes.
    
    int get_repeat_times() const;
    void set_repeat_times( int repeat_times );

    int get_current_repeat_times() const;
    void set_current_repeat_times( int repeat_times );
    //int get_tick_result() const;
    //void set_tick_result( int tick_result );

    // Handling functions.
    virtual void reset_bt_node() override;
    virtual int tick(Variant user_data, double delta) override;
};

}


#endif 
