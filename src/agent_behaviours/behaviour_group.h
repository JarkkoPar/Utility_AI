#ifndef UtilityAIBEHAVIOURGROUP_H_INCLUDED
#define UtilityAIBEHAVIOURGROUP_H_INCLUDED 

#include "utility_ai.h"
#include <godot_cpp/classes/node.hpp>
#include "resources/considerations/consideration_resources.h"
#include "considerations.h"
#include "behaviours.h"

namespace godot {

class UtilityAIBehaviourGroup : public UtilityAIBehaviours {
    GDCLASS(UtilityAIBehaviourGroup, UtilityAIBehaviours )

private:
    //float  _score;
    float  _activation_score;
    //TypedArray<UtilityAIConsiderationResources> _considerations;

    //std::vector<UtilityAIConsiderations*> _child_considerations;
    //unsigned int _num_child_considerations;
protected:
    static void _bind_methods();
    #ifdef DEBUG_ENABLED
    uint64_t     _last_evaluated_timestamp;
    uint64_t     _last_visited_timestamp;
    #endif
public:
    UtilityAIBehaviourGroup();
    ~UtilityAIBehaviourGroup();
    
    
    // Getters and setters for attributes.

    #ifdef DEBUG_ENABLED
    inline uint64_t get_last_visited_timestamp() const {return _last_visited_timestamp;};
    inline uint64_t get_last_evaluated_timestamp() const {return _last_evaluated_timestamp;};
    #endif

    void set_activation_score( float score );
    float get_activation_score() const override;

    //void  set_score( float score );
    //float get_score() const;

    void set_considerations( TypedArray<UtilityAIConsiderationResources> considerations );
    TypedArray<UtilityAIConsiderationResources> get_considerations() const;

    
    // Handling functions.

    float evaluate() override;
    bool is_behaviour_group() const override { return true; };

    // Godot virtuals.
    //void _notification(int p_what);

};

}


#endif 
