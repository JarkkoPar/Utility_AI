#ifndef UtilityAISTRoot_H_INCLUDED
#define UtilityAISTRoot_H_INCLUDED 

#include "nodes.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/dictionary.hpp>



namespace godot {

class UtilityAISTRoot : public UtilityAIStateTreeNodes {
    GDCLASS(UtilityAISTRoot, UtilityAIStateTreeNodes)

private:
    #ifdef DEBUG_ENABLED
    uint64_t                 _total_tick_usec;    
    uint64_t                 _total_transition_usec;
    #endif
    TypedArray<UtilityAIStateTreeNodes> _active_states;
    std::vector<UtilityAIStateTreeNodes*> _active_states_vector;

    Variant                  _ai_context;
    
protected:
    static void _bind_methods();
    std::vector<UtilityAISensors*>  _child_sensors;
    unsigned int _num_child_sensors;
public:
    UtilityAISTRoot();
    ~UtilityAISTRoot();
    
    
    // Getters and setters for attributes.
    #ifdef DEBUG_ENABLED
    uint64_t get_total_tick_usec() const;
    void set_total_tick_usec(uint64_t total_tick_usec );
    #endif 

    TypedArray<Node> get_active_states() const;

    //UtilityAIStateTreeNodes* get_active_state() const;
    //_active_states

    // Handling functions.
    //virtual TypedArray<UtilityAIStateTreeNodes> _tick( Variant user_data, float delta) override;
    virtual void transition_to( NodePath path_to_node, Variant user_data, float delta ) override;
    bool try_transition( UtilityAIStateTreeNodes* transition_target_node, Variant user_data, float delta );

    virtual void transition_to_no_params( NodePath path_to_node ) override;
    bool try_transition_no_params( UtilityAIStateTreeNodes* transition_target_node );


    void tick(Variant user_data, float delta);
    void tick_no_params();

    // Godot virtuals.
    void _ready() override;
};

}


#endif 
