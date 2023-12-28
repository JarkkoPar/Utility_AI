#ifndef UTILITYAIAGENT_H_INCLUDED
#define UTILITYAIAGENT_H_INCLUDED 

#include "utility_ai.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include "performance_monitor_singleton.h"
#include "agent_behaviours/behaviour.h"
#include "agent_behaviours/action.h"


#define UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS 16

namespace godot {

class UtilityAIAgent : public UtilityAI {
    GDCLASS(UtilityAIAgent, UtilityAI)

private:
    RandomNumberGenerator _rng;
    //Node* _current_behaviour_node;
    //Node* _current_action_node;
    UtilityAIBehaviour* _current_behaviour_node;
    UtilityAIAction*    _current_action_node;

    float  _current_behaviour_bias;

    int    _num_behaviours_to_select;
    int    _num_possible_behaviours;
    //int    _top_scoring_behaviours[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    UtilityAIBehaviour*  _top_scoring_behaviours_nodes[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    float _top_scoring_behaviours_score[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    godot::String _top_scoring_behaviour_name;
    godot::String _current_behaviour_name;
    
    float _thinking_delay_in_seconds;
    float _thinking_delay_in_seconds_current_timer;

    uint64_t _total_evaluate_options_usec;
    uint64_t _total_update_behaviour_usec;

protected:
    static void _bind_methods();
    void place_into_top_n_behaviour_list(UtilityAIBehaviour* behaviour, float score );

public:
    UtilityAIAgent();
    ~UtilityAIAgent();
    
    
    // Getters and setters for attributes.
    
    void set_thinking_delay_in_seconds( float thinking_delay_in_seconds );
    float get_thinking_delay_in_seconds() const;

    void set_current_behaviour_node( UtilityAIBehaviour* new_behaviour_node );
    UtilityAIBehaviour* get_current_behaviour_node() const;

    //void set_current_behaviour_index( int current_behaviour_index );
    //int  get_current_behaviour_index() const;

    void          set_current_behaviour_name( godot::String current_behaviour_name );
    godot::String get_current_behaviour_name() const;
    
    void set_num_behaviours_to_select( int num_behaviours_to_select );
    int  get_num_behaviours_to_select() const;
    
    void set_current_behaviour_bias( float current_behaviour_bias );
    float get_current_behaviour_bias() const;

    void set_top_scoring_behaviour_name( godot::String top_scoring_behaviour_name );
    godot::String get_top_scoring_behaviour_name() const;

    void set_current_action_node( UtilityAIAction* new_action_node );
    UtilityAIAction* get_current_action_node() const;

    void set_total_evaluate_options_usec( uint64_t total_evaluate_options_usec );
    uint64_t get_total_evaluate_options_usec() const;

    void set_total_update_behaviour_usec( uint64_t total_update_behaviour_usec );
    uint64_t get_total_update_behaviour_usec() const;

    //void set_random_number_generator( RandomNumberGenerator rng );
    //RandomNumberGenerator get_random_number_generator() const;

    // Handling functions.

    void evaluate_options(float delta);

    void update_current_behaviour();

    void set_current_action_is_finished(bool is_finished);
    void abort_current_behaviour();
};

}


#endif 
