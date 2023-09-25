#ifndef UtilityAIBehaviour_H_INCLUDED
#define UtilityAIBehaviour_H_INCLUDED 

#include "UtilityAI.h"
#include "UtilityAIAgent.h"
#include <godot_cpp/classes/node.hpp>


namespace godot {

class UtilityAIBehaviour : public UtilityAI {
    GDCLASS(UtilityAIBehaviour, UtilityAI )

private:
    double _cooldown_seconds;
    double _current_cooldown_seconds;
    float _score;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBehaviour();
    ~UtilityAIBehaviour();
    
    
    // Getters and setters for attributes.
    /**/
    
    
    void  set_score( float score );
    float get_score() const;
    
    void  set_cooldown_seconds( double cooldown_seconds );
    double get_cooldown_seconds() const;


    /**/
    // Godot virtuals.
    void _ready();
    /**
    void _process(double delta);
    void _physics_process(double delta);
    /**/
    void _notification(int p_what);

    // Handling functions.

    float evaluate(UtilityAIAgent* agent, double delta);
    void  start_behaviour();
    void  end_behaviour();
};

}


#endif 
