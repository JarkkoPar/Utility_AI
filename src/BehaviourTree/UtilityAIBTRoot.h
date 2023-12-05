#ifndef UtilityAIBTRoot_H_INCLUDED
#define UtilityAIBTRoot_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTRoot : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTRoot, UtilityAIBehaviourTreeNodes)

private:
    uint64_t            _total_tick_usec;    
protected:
    static void _bind_methods();

public:
    UtilityAIBTRoot();
    ~UtilityAIBTRoot();
    
    
    // Getters and setters for attributes.
    
    uint64_t get_total_tick_usec() const;
    void set_total_tick_usec(uint64_t total_tick_usec );

    // Handling functions.

    virtual int tick(Variant user_data, double delta) override;
};

}


#endif 
