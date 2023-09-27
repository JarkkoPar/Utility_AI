#ifndef UTILITYAIAGENT_H_INCLUDED
#define UTILITYAIAGENT_H_INCLUDED 

#include "UtilityAI.h"

#include <godot_cpp/classes/node.hpp>

#define UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS 16

namespace godot {

class UtilityAIAgent : public UtilityAI {
    GDCLASS(UtilityAIAgent, UtilityAI)

private:
    
    Node* _chosen_behaviour_node;

    int   _num_behaviours_to_select;
    int   _top_scoring_behaviours[UTILITYAIAGENT_MAX_TOP_SCORING_BEHAVIOURS];
    
protected:
    static void _bind_methods();

public:
    UtilityAIAgent();
    ~UtilityAIAgent();
    
    
    // Getters and setters for attributes.
    
    void set_current_behaviour( Node* new_behaviour );
    Node* get_current_behaviour() const;
    
    void set_num_behaviours_to_select( int num_behaviours_to_select );
    int  get_num_behaviours_to_select() const;
    
    
    /**    
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */
    // Handling functions.

    void evaluate_options();//double delta);
};

}


#endif 
