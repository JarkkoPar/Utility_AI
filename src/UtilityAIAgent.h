#ifndef UTILITYAIAGENT_H_INCLUDED
#define UTILITYAIAGENT_H_INCLUDED 

#include "UtilityAI.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


#define UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS 16

namespace godot {

class UtilityAIAgent : public UtilityAI {
    GDCLASS(UtilityAIAgent, UtilityAI)

private:
    RandomNumberGenerator _rng;
    Node* _current_behaviour_node;
    Node* _current_action_node;

    int    _num_behaviours_to_select;
    int    _num_possible_behaviours;
    //int    _top_scoring_behaviours[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    Node*  _top_scoring_behaviours_nodes[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    double _top_scoring_behaviours_score[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    godot::String _top_scoring_behaviour_name;
    godot::String _current_behaviour_name;
    
    double _thinking_delay_in_seconds;
    double _thinking_delay_in_seconds_current_timer;

    uint64_t _total_evaluate_options_usec;
protected:
    static void _bind_methods();
    void place_into_top_n_behaviour_list(Node* behaviour, float score );

public:
    UtilityAIAgent();
    ~UtilityAIAgent();
    
    
    // Getters and setters for attributes.
    
    void set_thinking_delay_in_seconds( double thinking_delay_in_seconds );
    double get_thinking_delay_in_seconds() const;

    void set_current_behaviour_node( Node* new_behaviour_node );
    Node* get_current_behaviour_node() const;

    //void set_current_behaviour_index( int current_behaviour_index );
    //int  get_current_behaviour_index() const;

    void          set_current_behaviour_name( godot::String current_behaviour_name );
    godot::String get_current_behaviour_name() const;
    
    void set_num_behaviours_to_select( int num_behaviours_to_select );
    int  get_num_behaviours_to_select() const;
    
    void set_top_scoring_behaviour_name( godot::String top_scoring_behaviour_name );
    godot::String get_top_scoring_behaviour_name() const;

    void set_current_action_node( Node* new_action_node );
    Node* get_current_action_node() const;

    void set_total_evaluate_options_usec( uint64_t total_evaluate_options_usec );
    uint64_t get_total_evaluate_options_usec() const;

    //void set_random_number_generator( RandomNumberGenerator rng );
    //RandomNumberGenerator get_random_number_generator() const;

    // Handling functions.

    void evaluate_options(double delta);

    void update_current_behaviour();

    void set_current_action_is_finished(bool is_finished);
    void abort_current_behaviour();
};

}


#endif 
