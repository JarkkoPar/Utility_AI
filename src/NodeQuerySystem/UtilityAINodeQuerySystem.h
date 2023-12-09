#ifndef UtilityAINodeQuerySystem_H_INCLUDED
#define UtilityAINodeQuerySystem_H_INCLUDED 

//#include "UtilityAINodeQuerySystem.h"
#include "../UtilityAI.h"
#include <godot_cpp/classes/node.hpp>
#include "SearchSpaces/UtilityAINQSSearchSpaces.h"
#include "SearchCriteria/UtilityAINQSSearchCriteria.h"

#include <vector>

namespace godot {

class UtilityAINodeQuerySystem : public UtilityAI { 
    GDCLASS(UtilityAINodeQuerySystem, UtilityAI) 

private:
    godot::TypedArray<UtilityAINQSSearchSpaces> _high_priority_queries;
    godot::TypedArray<UtilityAINQSSearchSpaces> _reqular_queries;
    int _current_high_priority_query_index;
    int _current_regular_query_index;
    uint64_t _time_budget_per_frame;
    uint64_t _time_budget_per_frame_high_priority_queries;
    uint64_t _time_budget_per_frame_regular_queries;
    float    _time_allocation_pct_to_high_priority_queries;

protected:
    static void _bind_methods();

public:
    UtilityAINodeQuerySystem();
    ~UtilityAINodeQuerySystem();
    
    
    // Getters and setters.

    void set_time_budget_per_frame( uint64_t time_budget_per_frame );
    uint64_t get_time_budget_per_frame() const;

    void set_time_allocation_pct_to_high_priority_queries( float time_allocation_pct_to_high_priority_queries );
    float get_time_allocation_pct_to_high_priority_queries() const;


    // Handling methods.
    
    int post_query( UtilityAINQSSearchSpaces* search_space, bool is_high_priority = true );
    //virtual bool execute_query(uint64_t time_budget_usec = 0 );

    
    // Godot virtuals.
    //void _ready();
    void _physics_process(float delta );
    //void _exit_tree();
};

}


#endif 
