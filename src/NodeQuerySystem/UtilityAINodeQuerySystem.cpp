#include "UtilityAINodeQuerySystem.h"


using namespace godot;


UtilityAINodeQuerySystem::UtilityAINodeQuerySystem() {
    _time_budget_per_frame = 200;
    _current_high_priority_query_index = 0;
    _current_regular_query_index = 0;

    _time_allocation_pct_to_high_priority_queries = 0.8f;
    _time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * (float)_time_budget_per_frame);
    _time_budget_per_frame_regular_queries = _time_budget_per_frame - _time_budget_per_frame_high_priority_queries;
}


UtilityAINodeQuerySystem::~UtilityAINodeQuerySystem() {
    
}

void UtilityAINodeQuerySystem::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_time_budget_per_frame", "time_budget_per_frame"), &UtilityAINodeQuerySystem::set_time_budget_per_frame);
    ClassDB::bind_method(D_METHOD("get_time_budget_per_frame"), &UtilityAINodeQuerySystem::get_time_budget_per_frame);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "time_budget_per_frame", PROPERTY_HINT_RANGE, "1,10000,or_greater"), "set_time_budget_per_frame","get_time_budget_per_frame");
    
    ClassDB::bind_method(D_METHOD("set_time_allocation_pct_to_high_priority_queries", "time_allocation_pct_to_high_priority_queries"), &UtilityAINodeQuerySystem::set_time_allocation_pct_to_high_priority_queries);
    ClassDB::bind_method(D_METHOD("get_time_allocation_pct_to_high_priority_queries"), &UtilityAINodeQuerySystem::get_time_allocation_pct_to_high_priority_queries);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "time_allocation_pct_to_high_priority_queries", PROPERTY_HINT_RANGE, "1,10000,or_greater"), "set_time_allocation_pct_to_high_priority_queries","get_time_allocation_pct_to_high_priority_queries");
    
    ClassDB::bind_method(D_METHOD("post_query", "search_space", "is_high_priority"), &UtilityAINodeQuerySystem::post_query);
    
}


// Getters and setters.

void UtilityAINodeQuerySystem::set_time_budget_per_frame( uint64_t time_budget_per_frame ) {
    _time_budget_per_frame = time_budget_per_frame;
}


uint64_t UtilityAINodeQuerySystem::get_time_budget_per_frame() const {
    return _time_budget_per_frame;
}


void UtilityAINodeQuerySystem::set_time_allocation_pct_to_high_priority_queries( float time_allocation_pct_to_high_priority_queries ) {
    _time_allocation_pct_to_high_priority_queries = time_allocation_pct_to_high_priority_queries;
    _time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * (float)_time_budget_per_frame);
    _time_budget_per_frame_regular_queries = _time_budget_per_frame - _time_budget_per_frame_high_priority_queries;
}


float UtilityAINodeQuerySystem::get_time_allocation_pct_to_high_priority_queries() const {
    return _time_allocation_pct_to_high_priority_queries;
}



// Godot virtuals.

void UtilityAINodeQuerySystem::_physics_process(float delta ) {
    std::vector<int> high_priority_queries_to_delete;
    uint64_t time_left_high_priority = _time_budget_per_frame_high_priority_queries;
    while( time_left_high_priority > 0 ) {
        UtilityAINQSSearchSpaces* current_query = godot::Object::cast_to<UtilityAINQSSearchSpaces>(_high_priority_queries[_current_high_priority_query_index]);
        if( current_query == nullptr ) {
            high_priority_queries_to_delete.push_back(_current_high_priority_query_index);
            ++_current_high_priority_query_index;
            continue;
        }

        bool is_completed = current_query->execute_query(1);
        time_left_high_priority -= current_query->get_current_call_runtime_usec();
        if( is_completed ) {
            high_priority_queries_to_delete.push_back(_current_high_priority_query_index);
        }
        
        ++_current_high_priority_query_index;
        if( _current_high_priority_query_index >= _high_priority_queries.size()) {
            // Delete the queries that have completed.
            for( int i = high_priority_queries_to_delete.size() - 1; i > -1; --i ) {
                _high_priority_queries.remove_at(high_priority_queries_to_delete[i]);
            }
            _current_high_priority_query_index = 0;
            high_priority_queries_to_delete.clear();
        }
    }

    /**
    uint64_t time_left_regular = _time_budget_per_frame_regular_queries;
    while( time_left_regular > 0 ) {
        UtilityAINQSSearchSpaces* current_query = _high_priority_queries[_current_high_priority_query_index];
        if( current_query == nullptr ) {
            ++_current_high_priority_query_index;
            continue;
        }
        bool is_completed = current_query->execute_query(1);
        time_left_regular -= current_query->get_current_call_runtime_usec();
    }
    /**/
    
}


// Handling methods.


int UtilityAINodeQuerySystem::post_query( UtilityAINQSSearchSpaces* search_space, bool is_high_priority ) {
    if( is_high_priority ) {
        if( _high_priority_queries.has( search_space ) ){
            return -1;
        }
        _high_priority_queries.push_back(search_space);
        return 1;
    }

    return -1;
}
