#ifndef UtilityAIBehaviour_H_INCLUDED
#define UtilityAIBehaviour_H_INCLUDED 

#include "utility_ai.h"
//#include "agent.h"
#include <godot_cpp/classes/node.hpp>

#include "action.h"
#include "action_group.h"
#include "../resources/considerations/consideration_resources.h"


namespace godot {

class UtilityAIBehaviour : public UtilityAI {
    GDCLASS(UtilityAIBehaviour, UtilityAI )

private:
    float  _cooldown_seconds;
    float  _current_cooldown_seconds;
    int    _cooldown_turns;
    int    _current_cooldown_turns;
    float  _score;
    int    _behaviour_id;
    int    _current_action_index;

    //UtilityAIAction*  _current_action_node;
    
    bool   _can_be_interrupted;
    TypedArray<UtilityAIConsiderationResources> _considerations;
protected:
    static void _bind_methods();

public:
    UtilityAIBehaviour();
    ~UtilityAIBehaviour();
    
    
    // Getters and setters for attributes.

    void  set_behaviour_id( int behaviour_id );
    int   get_behaviour_id() const;

    void  set_can_be_interrupted( bool can_be_interrupted );
    bool  get_can_be_interrupted() const;
    
    void  set_score( float score );
    float get_score() const;
    
    void  set_cooldown_seconds( float cooldown_seconds );
    float get_cooldown_seconds() const;

    void  set_cooldown_turns( int cooldown_turns );
    int   get_cooldown_turns() const;

    void  set_current_action_index( int current_action_index );
    int   get_current_action_index() const;

    void set_considerations( TypedArray<UtilityAIConsiderationResources> considerations );
    TypedArray<UtilityAIConsiderationResources> get_considerations() const;

    //UtilityAIAction* get_current_action_node() const { return _current_action_node;};

    // Godot virtuals.
    void _ready();
    
    void _process(float delta);
    void _notification(int p_what);

    // Handling functions.

    float evaluate();//UtilityAIAgent* agent);
    void  start_behaviour();
    void  end_behaviour();
    UtilityAIAction* update_behaviour();

    Node* step_actions();
};

}


#endif 
