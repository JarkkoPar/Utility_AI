#ifndef UTILITYAIAGENT_H_INCLUDED
#define UTILITYAIAGENT_H_INCLUDED 

#include "UtilityAI.h"

#include <godot_cpp/classes/node.hpp>

#define UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS 16

namespace godot {

class UtilityAIAgent : public UtilityAI {
    GDCLASS(UtilityAIAgent, UtilityAI)

private:
    
    int   _current_behaviour_index;
    Node* _current_behaviour_node;

    Node* _current_action_node;

    int    _num_behaviours_to_select;
    int    _top_scoring_behaviours[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    double _top_scoring_behaviours_score[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    godot::String _top_scoring_behaviour_name;
    godot::String _current_behaviour_name;
    
protected:
    static void _bind_methods();

public:
    UtilityAIAgent();
    ~UtilityAIAgent();
    
    
    // Getters and setters for attributes.
    
    void set_current_behaviour_node( Node* new_behaviour_node );
    Node* get_current_behaviour_node() const;

    void set_current_behaviour_index( int current_behaviour_index );
    int  get_current_behaviour_index() const;

    void          set_current_behaviour_name( godot::String current_behaviour_name );
    godot::String get_current_behaviour_name() const;
    
    void set_num_behaviours_to_select( int num_behaviours_to_select );
    int  get_num_behaviours_to_select() const;
    
    void set_top_scoring_behaviour_name( godot::String top_scoring_behaviour_name );
    godot::String get_top_scoring_behaviour_name() const;

    void set_current_action_node( Node* new_action_node );
    Node* get_current_action_node() const;

    /**    
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */
    // Handling functions.

    void evaluate_options();

    void update_current_behaviour();
};

}


#endif 
