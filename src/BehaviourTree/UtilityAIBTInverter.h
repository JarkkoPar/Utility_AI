#ifndef UtilityAIBTInverter_H_INCLUDED
#define UtilityAIBTInverter_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTInverter : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTInverter, UtilityAIBehaviourTreeNodes)

private:
    
    //int _tick_result;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTInverter();
    ~UtilityAIBTInverter();
    
    
    // Getters and setters for attributes.
        
    //void set_tick_result( int tick_result );
    //int  get_tick_result() const;

    // Handling functions.

    virtual int tick(Variant user_data, double delta) override;
};

}


#endif 
