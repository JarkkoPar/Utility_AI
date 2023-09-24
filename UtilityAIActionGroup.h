#ifndef UtilityAIActionGroup_H_INCLUDED
#define UtilityAIActionGroup_H_INCLUDED 


#include "UtilityAIActionBase.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIActionGroup : public UtilityAIActionBase {
    GDCLASS(UtilityAIActionGroup, UtilityAIActionBase )

private:
    
protected:
    static void _bind_methods();

public:
    UtilityAIActionGroup();
    ~UtilityAIActionGroup();
    
    
    // Getters and setters for attributes.
    /**
  
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
