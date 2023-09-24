#ifndef AIBEHAVIOUR_H_INCLUDED
#define AIBEHAVIOUR_H_INCLUDED 

//#include "AIBehaviourState.h"

#include <godot_cpp/classes/node.hpp>


namespace godot {

class AIBehaviour : public Node {
    GDCLASS(AIBehaviour, Node)

private:
    bool _is_active; 
    //int  _update_method;

    float _score;
    
protected:
    static void _bind_methods();

public:
    AIBehaviour();
    ~AIBehaviour();
    
    
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
