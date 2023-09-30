#ifndef UtilityAIBehaviour_H_INCLUDED
#define UtilityAIBehaviour_H_INCLUDED 

#include "UtilityAI.h"
#include "UtilityAIAgent.h"
#include <godot_cpp/classes/node.hpp>

#include "UtilityAIAction.h"
#include "UtilityAIActionGroup.h"



namespace godot {

class UtilityAIBehaviour : public UtilityAI {
    GDCLASS(UtilityAIBehaviour, UtilityAI )

private:
    double _cooldown_seconds;
    double _current_cooldown_seconds;
    float  _score;

    int    _current_action_index;

    UtilityAIAction*  _current_action_node;
    
    bool   _can_be_interrupted;

protected:
    static void _bind_methods();

public:
    UtilityAIBehaviour();
    ~UtilityAIBehaviour();
    
    
    // Getters and setters for attributes.
    /**/
    
    void  set_can_be_interrupted( bool can_be_interrupted );
    bool  get_can_be_interrupted() const;
    
    void  set_score( float score );
    float get_score() const;
    
    void  set_cooldown_seconds( double cooldown_seconds );
    double get_cooldown_seconds() const;

    void  set_current_action_index( int current_action_index );
    int   get_current_action_index() const;

    /**/
    // Godot virtuals.
    void _ready();
    /**
    void _process(double delta);
    void _physics_process(double delta);
    /**/
    void _notification(int p_what);

    // Handling functions.

    double evaluate();
    void  start_behaviour();
    void  end_behaviour();
    UtilityAIAction* update_behaviour();

    Node* step_actions();
};

}


#endif 
