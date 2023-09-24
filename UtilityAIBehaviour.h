#ifndef UtilityAIBehaviour_H_INCLUDED
#define UtilityAIBehaviour_H_INCLUDED 

//#include "UtilityAIBehaviourState.h"

#include <godot_cpp/classes/node.hpp>


namespace godot {

class UtilityAIBehaviour : public Node {
    GDCLASS(UtilityAIBehaviour, Node)

private:
    bool _is_active; 
    //int  _update_method;

    float _score;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBehaviour();
    ~UtilityAIBehaviour();
    
    
    // Getters and setters for attributes.
    /**/
    void  set_is_active( bool is_active );
    bool  get_is_active() const;
    
    void  set_score( float score );
    float get_score() const;
    
    /**/
    //void set_update_method( int update_method );
    //int  get_update_method() const;
    /**/
    // Godot virtuals.
    void _ready();
    /**
    void _process(double delta);
    void _physics_process(double delta);
    /**/
    void _notification(int p_what);

    // Handling functions.

    float evaluate();
};

}


#endif 
