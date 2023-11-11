#ifndef UtilityAIActionGroup_H_INCLUDED
#define UtilityAIActionGroup_H_INCLUDED 


#include "UtilityAIActions.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>



namespace godot {

class UtilityAIActionGroup : public UtilityAIActions {
    GDCLASS(UtilityAIActionGroup, UtilityAIActions )

private:
    int _action_execution_rule;
    int _error_handling_rule;
    int _current_action_index;
    bool _if_else_boolean_value;

    RandomNumberGenerator _rnd;
            
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
        PickOneAtRandom = 1,
        IfElse = 2,
        CustomRule = 3,
        //IfPreviousActionFailedElse = 4,
    };

    void set_error_handling_rule( int error_handling_rule );
    int  get_error_handling_rule() const;

    enum UtilityAIActionGroupErrorHandlingRule {
        EndExecution = 0,
        ContinueExecution = 1,
    };

    void  set_current_action_index( int current_action_index );
    int   get_current_action_index() const;

    void  set_if_else_boolean_value( bool if_else_boolean_value );
    bool  get_if_else_boolean_value() const;

    // Handling functions.

    virtual bool start_action() override; 
    virtual bool end_action() override;
    virtual Node* step_actions() override;
};

}


#endif 
