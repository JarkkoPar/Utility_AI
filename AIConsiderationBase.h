#ifndef AICONSIDERATIONBASE_H_INCLUDED
#define AICONSIDERATIONBASE_H_INCLUDED 

//#include "AIConsiderationState.h"

#include <godot_cpp/classes/node.hpp>



namespace godot {

class AIConsiderationBase : public Node {
    GDCLASS(AIConsiderationBase, Node)

private:
    

    
protected:
    static void _bind_methods();

    bool _is_active; 
    float _score;
    bool _has_vetoed;

public:
    AIConsiderationBase();
    ~AIConsiderationBase();
    
    
    // Getters and setters for attributes.
    
    void  set_is_active( bool is_active );
    bool  get_is_active() const;
    
    void  set_has_vetoed( bool has_vetoed );
    bool  get_has_vetoed() const;

    void set_score( float score );
    float get_score() const;

    /**
    void set_update_method( int update_method );
    int  get_update_method() const;
        
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */

    // Handling functions.

    virtual float evaluate();
};

}


#endif 
