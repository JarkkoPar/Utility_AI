#ifndef AIACTION_H_INCLUDED
#define AIACTION_H_INCLUDED 

//#include "AIActionState.h"

#include <godot_cpp/classes/node.hpp>



namespace godot {

class AIAction : public Node {
    GDCLASS(AIAction, Node)

private:
    bool _is_active; 
    //int  _update_method;


    
protected:
    static void _bind_methods();

public:
    AIAction();
    ~AIAction();
    
    
    // Getters and setters for attributes.
    /**
    void  set_is_active( bool is_active );
    bool  get_is_active() const;
    
    void set_update_method( int update_method );
    int  get_update_method() const;
        
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);

    // Handling functions.

    bool _change_to_state( String target_state_name );

    void _update_current_state(double delta);
    */
};

}


#endif 
