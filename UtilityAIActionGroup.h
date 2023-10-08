#ifndef UtilityAIActionGroup_H_INCLUDED
#define UtilityAIActionGroup_H_INCLUDED 


#include "UtilityAIActions.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIActionGroup : public UtilityAIActions {
    GDCLASS(UtilityAIActionGroup, UtilityAIActions )

private:
    int _action_execution_rule;
    //int _action_execution_index;

    int _current_action_index;
    
protected:
    static void _bind_methods();

public:
    UtilityAIActionGroup();
    ~UtilityAIActionGroup();
    
    
    // Getters and setters for attributes.

    void set_action_execution_rule( int action_execution_rule );
    int get_action_execution_rule() const;

    enum UtilityAIActionGroupExecutionRule {
        Sequence = 0,
        PickOneAtRandom=1
    };


    void  set_current_action_index( int current_action_index );
    int   get_current_action_index() const;

    // Handling functions.

    virtual bool start_action() override; 
    virtual bool end_action() override;
    virtual Node* step_actions() override;
};

}


#endif 
