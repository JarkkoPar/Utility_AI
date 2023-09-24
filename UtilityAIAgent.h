#ifndef UTILITYAIAGENT_H_INCLUDED
#define UTILITYAIAGENT_H_INCLUDED 


#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIAgent : public Node {
    GDCLASS(UtilityAIAgent, Node)

private:
    bool _is_active; 
    //int  _update_method;

    Node* _chosen_behaviour_node;
    
protected:
    static void _bind_methods();

public:
    UtilityAIAgent();
    ~UtilityAIAgent();
    
    
    // Getters and setters for attributes.
    
    void  set_is_active( bool is_active );
    bool  get_is_active() const;

    /**    
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */
    // Handling functions.

    void evaluate_options();
};

}


#endif 
