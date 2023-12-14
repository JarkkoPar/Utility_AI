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
    godot::TypedArray<UtilityAINQSSearchSpaces> _regular_queries;
    int _current_high_priority_query_index;
    int _current_regular_query_index;
    uint64_t _post_query_time_budget_per_frame;
    uint64_t _run_queries_time_budget_per_frame;
    uint64_t _run_queries_time_budget_per_frame_high_priority_queries;
    uint64_t _run_queries_time_budget_per_frame_regular_queries;
    float    _time_allocation_pct_to_high_priority_queries;
    bool     _is_performance_counter_initialized;
    uint64_t _run_queries_time_elapsed_usec;
    uint64_t _current_post_high_priority_queries_time_elapsed_usec;
    uint64_t _current_post_regular_queries_time_elapsed_usec;
    uint64_t _post_high_priority_queries_time_elapsed_usec;
    uint64_t _post_regular_queries_time_elapsed_usec;
    uint64_t _post_query_time_budget_per_frame_high_priority_queries;
    uint64_t _post_query_time_budget_per_frame_regular_queries;
protected:
    static void _bind_methods();

public:
    UtilityAINodeQuerySystem();
    ~UtilityAINodeQuerySystem();
    
    
    // Getters and setters.

    void set_post_query_time_budget_per_frame( uint64_t post_query_time_budget_per_frame );
    uint64_t get_post_query_time_budget_per_frame() const;

    void set_run_queries_time_budget_per_frame( uint64_t time_budget_per_frame );
    uint64_t get_run_queries_time_budget_per_frame() const;

    void set_time_allocation_pct_to_high_priority_queries( float time_allocation_pct_to_high_priority_queries );
    float get_time_allocation_pct_to_high_priority_queries() const;

    int  get_run_queries_time_elapsed_usec() const;
    int  get_post_queries_time_elapsed_usec() const;

    // Handling methods.
    void initialize_performance_counters();
    
    int post_query( UtilityAINQSSearchSpaces* search_space, bool is_high_priority = true );
    void run_queries();
    void clear_queries();


    
    // Godot virtuals.
    //void _ready();
    //void _exit_tree();
};

}


#endif 
