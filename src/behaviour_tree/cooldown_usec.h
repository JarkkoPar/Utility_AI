#ifndef UtilityAIBTCooldownUsec_H_INCLUDED
#define UtilityAIBTCooldownUsec_H_INCLUDED 

#include "decorator_nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBTCooldownUsec : public UtilityAIBTDecoratorNodes {
    GDCLASS(UtilityAIBTCooldownUsec, UtilityAIBTDecoratorNodes)

private:
    
    
    uint64_t _cooldown_usec;
    uint64_t _cooldown_start_timestamp;

    int _cooldown_return_value;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTCooldownUsec();
    ~UtilityAIBTCooldownUsec();
    
    
    // Getters and setters for attributes.
        
    void set_cooldown_usec( int cooldown_usec );
    int  get_cooldown_usec() const;

    void set_cooldown_start_timestamp( int cooldown_Usec );
    int  get_cooldown_start_timestamp() const;

    void set_cooldown_return_value( int cooldown_return_value );
    int  get_cooldown_return_value() const;

    // Handling functions.

    virtual int tick(Variant user_data, float delta) override;
};

}


#endif 
