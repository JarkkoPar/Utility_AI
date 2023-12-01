#ifndef UtilityAIBTAgent_H_INCLUDED
#define UtilityAIBTAgent_H_INCLUDED 

#include "UtilityAI.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTAgent : public UtilityAI {
    GDCLASS(UtilityAIBTAgent, UtilityAI)

private:
    uint64_t            _total_tick_usec;    
protected:
    static void _bind_methods();

public:
    UtilityAIBTAgent();
    ~UtilityAIBTAgent();
    
    
    // Getters and setters for attributes.
    
    uint64_t get_total_tick_usec() const;
    void set_total_tick_usec(uint64_t total_tick_usec );

    // Handling functions.

    int tick(Variant user_data, double delta);
};

}


#endif 
