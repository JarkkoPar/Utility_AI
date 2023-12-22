#ifndef UtilityAIStateTreeNodes_H_INCLUDED
#define UtilityAIStateTreeNodes_H_INCLUDED 

#include "utility_ai.h"
#include <godot_cpp/classes/node.hpp>
#include "../resources/considerations/consideration_resources.h"


namespace godot {

class UtilityAIStateTreeNodes : public UtilityAI {
    GDCLASS(UtilityAIStateTreeNodes, UtilityAI)

private:
    double _score;
    int    _evaluation_method;
    bool   _invert_score;
    int    _child_state_selection_rule;
    UtilityAIStateTreeNodes* _tree_root_node;
    TypedArray<UtilityAIConsiderationResources>    _considerations;
protected:
    static void _bind_methods();
public:
    UtilityAIStateTreeNodes();
    ~UtilityAIStateTreeNodes();
    
    
    // Getters and setters for attributes.

    void set_considerations( TypedArray<UtilityAIConsiderationResources> considerations );
    TypedArray<UtilityAIConsiderationResources> get_considerations() const;
    
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

    void set_child_state_selection_rule( int child_state_selection_rule );
    int  get_child_state_selection_rule() const;

    Dictionary get_child_nodes_as_dictionary(UtilityAIStateTreeNodes* tree_root_node );

    //inline virtual bool get_is_leaf() const { return false; };
    
    enum UtilityAIStateTreeNodeChildStateSelectionRule {
        ON_ENTER_CONDITION_METHOD = 0,
        UTILITY_SCORING = 1,
    };

    // Handling functions.
    
    virtual double evaluate();
    virtual bool   on_enter_condition( Variant user_data, double delta );
    virtual void   on_enter_state( Variant user_data, double delta );
    virtual void   on_exit_state( Variant user_data, double delta );
    virtual void   on_tick( Variant user_data, double delta );
    virtual void   transition_to( godot::String new_state_name, Variant user_data, double delta );

    virtual UtilityAIStateTreeNodes* evaluate_state_activation( Variant user_data, double delta );
    

    // Godot virtuals.
    // none.
    
};

}


#endif 
