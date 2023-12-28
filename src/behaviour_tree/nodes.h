#ifndef UtilityAIBehaviourTreeNodes_H_INCLUDED
#define UtilityAIBehaviourTreeNodes_H_INCLUDED 

#include "../utility_ai.h"
#include "definitions.h"
#include <godot_cpp/classes/node.hpp>
#include "../resources/considerations/consideration_resources.h"



namespace godot {

class UtilityAIBehaviourTreeNodes : public UtilityAI {
    GDCLASS(UtilityAIBehaviourTreeNodes, UtilityAI)

private:
    float _score;
    int    _evaluation_method;
    bool   _invert_score;
    int    _tick_result;
    int    _internal_status;
    int    _reset_rule;
    bool   _has_reset_rule_changed;

    TypedArray<UtilityAIConsiderationResources> _considerations;

protected:
    static void _bind_methods();
public:
    UtilityAIBehaviourTreeNodes();
    ~UtilityAIBehaviourTreeNodes();
    
    
    // Getters and setters for attributes.

    void set_considerations( TypedArray<UtilityAIConsiderationResources> considerations );
    TypedArray<UtilityAIConsiderationResources> get_considerations() const;

    
    void set_evaluation_method( int evaluation_method );
    int  get_evaluation_method() const;

    enum UtilityAIBehaviourTreeNodesEvaluationMethod {
        Sum = 0,
        Min=1,
        Max=2,
        Mean=3,
        Multiply=4,
        FirstNonZero=5,
        //OneMinusScore=6
    };
    
    void set_score( float score );
    float get_score() const;

    void set_tick_result( int tick_result );
    int  get_tick_result() const;

    void set_internal_status( int internal_status );
    int  get_internal_status() const;

    void set_reset_rule( int reset_rule );
    int  get_reset_rule() const;
    
    enum UtilityAIBehaviourTreeNodesResetRule {
        WHEN_TICKED = 0,
        WHEN_COMPLETED,
        WHEN_TICKED_AFTER_BEING_COMPLETED,
        NEVER,
    };

    // Handling functions.
    
    virtual float evaluate();

    virtual int tick( Variant user_data, float delta );

    virtual void reset();
    //virtual void reset_for_looping();
    virtual void reset_bt_node() {};

    inline virtual bool has_completed() { return (_internal_status == BT_INTERNAL_STATUS_COMPLETED); };

    // Godot virtuals.
    // none.
    
};

}


#endif 
