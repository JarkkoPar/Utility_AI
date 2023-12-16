#ifndef UtilityAIStateTreeNodes_H_INCLUDED
#define UtilityAIStateTreeNodes_H_INCLUDED 

#include "utility_ai.h"
#include "definitions.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIStateTreeNodes : public UtilityAI {
    GDCLASS(UtilityAIStateTreeNodes, UtilityAI)

private:
    double _score;
    int    _evaluation_method;
    bool   _invert_score;
    int    _tick_result;
    int    _internal_status;
    int    _reset_rule;
    bool   _has_reset_rule_changed;
protected:
    static void _bind_methods();
public:
    UtilityAIStateTreeNodes();
    ~UtilityAIStateTreeNodes();
    
    
    // Getters and setters for attributes.
    
    void set_evaluation_method( int evaluation_method );
    int  get_evaluation_method() const;

    enum UtilityAIStateTreeNodesEvaluationMethod {
        Sum = 0,
        Min=1,
        Max=2,
        Mean=3,
        Multiply=4,
        FirstNonZero=5,
        //OneMinusScore=6
    };
    
    void set_score( double score );
    double get_score() const;

    void set_tick_result( int tick_result );
    int  get_tick_result() const;

    void set_internal_status( int internal_status );
    int  get_internal_status() const;

    void set_reset_rule( int reset_rule );
    int  get_reset_rule() const;
    
    enum UtilityAIStateTreeNodesResetRule {
        WHEN_TICKED = 0,
        WHEN_COMPLETED,
        WHEN_TICKED_AFTER_BEING_COMPLETED,
        NEVER,
    };

    // Handling functions.
    
    virtual double evaluate();
    virtual bool   on_enter_condition( Variant user_data, double delta );

    virtual UtilityAIStateTreeNodes* tick( Variant user_data, double delta );

    virtual void reset();
    //virtual void reset_for_looping();
    virtual void reset_st_node() {};

    inline virtual bool has_completed() { return (_internal_status == ST_INTERNAL_STATUS_COMPLETED); };

    // Godot virtuals.
    // none.
    
};

}


#endif 
