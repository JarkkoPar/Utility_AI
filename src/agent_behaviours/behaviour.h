#ifndef UtilityAIBehaviour_H_INCLUDED
#define UtilityAIBehaviour_H_INCLUDED 

#include "utility_ai.h"
#include "agent.h"
#include <godot_cpp/classes/node.hpp>

#include "action.h"
#include "action_group.h"
#include "../resources/considerations/consideration_resources.h"


namespace godot {

class UtilityAIBehaviour : public UtilityAI {
    GDCLASS(UtilityAIBehaviour, UtilityAI )

private:
    double _cooldown_seconds;
    double _current_cooldown_seconds;
    int    _cooldown_turns;
    int    _current_cooldown_turns;
    double  _score;

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
    
    void  set_can_be_interrupted( bool can_be_interrupted );
    bool  get_can_be_interrupted() const;
    
    void  set_score( double score );
    double get_score() const;
    
    void  set_cooldown_seconds( double cooldown_seconds );
    double get_cooldown_seconds() const;

    void  set_cooldown_turns( int cooldown_turns );
    int   get_cooldown_turns() const;

    void  set_current_action_index( int current_action_index );
    int   get_current_action_index() const;

    void set_considerations( TypedArray<UtilityAIConsiderationResources> considerations );
    TypedArray<UtilityAIConsiderationResources> get_considerations() const;

    //UtilityAIAction* get_current_action_node() const { return _current_action_node;};

    // Godot virtuals.
    void _ready();
    
    void _process(double delta);
    void _notification(int p_what);

    // Handling functions.

    double evaluate();//UtilityAIAgent* agent);
    void  start_behaviour();
    void  end_behaviour();
    UtilityAIAction* update_behaviour();

    Node* step_actions();
};

}


#endif 
