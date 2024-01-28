#ifndef UtilityAIStateTreeNodes_H_INCLUDED
#define UtilityAIStateTreeNodes_H_INCLUDED 

#include "utility_ai.h"
#include <godot_cpp/classes/node.hpp>
#include "../resources/considerations/consideration_resources.h"
#include "../agent_behaviours/considerations.h"

namespace godot {

class UtilityAIStateTreeNodes : public UtilityAI {
    GDCLASS(UtilityAIStateTreeNodes, UtilityAI)

private:
    bool    _is_on_entered_condition_true;
    float   _score;
    int     _evaluation_method;
    bool    _invert_score;
    int     _child_state_selection_rule;
    bool    _has_on_entered_method;
    bool    _has_on_exited_method;
    bool    _has_on_ticked_method;
    bool    _has_on_entered_condition_method;
    UtilityAIStateTreeNodes* _tree_root_node;
    TypedArray<UtilityAIConsiderationResources>    _considerations;
    std::vector<UtilityAIStateTreeNodes*>   _child_states;
    unsigned int _num_child_states;

    std::vector<UtilityAIConsiderations*> _child_considerations;
    unsigned int _num_child_considerations;
protected:
    static void _bind_methods();

    #ifdef DEBUG_ENABLED
    uint64_t     _last_evaluated_timestamp;
    uint64_t     _last_visited_timestamp;
    #endif
public:
    UtilityAIStateTreeNodes();
    ~UtilityAIStateTreeNodes();
    
    
    // Getters and setters for attributes.

    #ifdef DEBUG_ENABLED
    inline uint64_t get_last_visited_timestamp() const {return _last_visited_timestamp;};
    inline uint64_t get_last_evaluated_timestamp() const {return _last_evaluated_timestamp;};
    #endif

    void set_considerations( TypedArray<UtilityAIConsiderationResources> considerations );
    TypedArray<UtilityAIConsiderationResources> get_considerations() const;
    
    void set_is_on_entered_condition_true( bool is_on_entered_condition_true );
    bool get_is_on_entered_condition_true() const;

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
    
    void set_score( float score );
    float get_score() const;

    void set_child_state_selection_rule( int child_state_selection_rule );
    int  get_child_state_selection_rule() const;

    virtual void set_root_node( UtilityAIStateTreeNodes* tree_root_node );
    //Dictionary get_child_nodes_as_dictionary(UtilityAIStateTreeNodes* tree_root_node );

    //inline virtual bool get_is_leaf() const { return false; };
    
    enum UtilityAIStateTreeNodeChildStateSelectionRule {
        ON_ENTER_CONDITION_METHOD = 0,
        UTILITY_SCORING = 1,
    };

    // Handling functions.
    
    virtual float evaluate();
    virtual bool   on_enter_condition( Variant user_data, float delta );
    virtual void   on_enter_state( Variant user_data, float delta );
    virtual void   on_exit_state( Variant user_data, float delta );
    virtual void   on_tick( Variant user_data, float delta );
    virtual void   transition_to( NodePath path_to_node, Variant user_data, float delta );

    virtual UtilityAIStateTreeNodes* evaluate_state_activation( Variant user_data, float delta );
    

    // Godot virtuals.
    
    //void _enter_tree();
    void _notification(int p_what);
};

}


#endif 
