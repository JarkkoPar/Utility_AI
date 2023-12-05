#ifndef UtilityAIBehaviourTreeNodes_H_INCLUDED
#define UtilityAIBehaviourTreeNodes_H_INCLUDED 

#include "UtilityAI.h"
#include "UtilityAIBehaviourTreeDefinitions.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIBehaviourTreeNodes : public UtilityAI {
    GDCLASS(UtilityAIBehaviourTreeNodes, UtilityAI)

private:
    double _score;
    int    _evaluation_method;
    bool   _invert_score;
    int    _tick_result;
    int    _internal_status;
protected:
    static void _bind_methods();
public:
    UtilityAIBehaviourTreeNodes();
    ~UtilityAIBehaviourTreeNodes();
    
    
    // Getters and setters for attributes.
    
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
    
    void set_score( double score );
    double get_score() const;

    void set_tick_result( int tick_result );
    int  get_tick_result() const;

    void set_internal_status( int internal_status );
    int  get_internal_status() const;

    // Handling functions.
    
    virtual double evaluate();

    virtual int tick( Variant user_data, double delta );

    virtual void reset();

    inline virtual bool has_completed() { return (_internal_status == BT_INTERNAL_STATUS_COMPLETED); };

    // Godot virtuals.

    
};

}


#endif 
