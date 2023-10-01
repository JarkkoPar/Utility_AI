#ifndef UtilityAIAction_H_INCLUDED
#define UtilityAIAction_H_INCLUDED 

#include "UtilityAIActions.h"

#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIAction : public UtilityAIActions {
    GDCLASS(UtilityAIAction, UtilityAIActions)

private:
    int _action_id; 
    
protected:
    static void _bind_methods();

public:
    UtilityAIAction();
    ~UtilityAIAction();
    
    
    // Getters and setters for attributes.

    void set_action_id( int action_id );
    int  get_action_id() const;

    /**

        
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */

    // Handling functions.

    virtual bool start_action() override;
    virtual bool end_action() override;
    virtual Node* step_actions() override;

};

}


#endif 
