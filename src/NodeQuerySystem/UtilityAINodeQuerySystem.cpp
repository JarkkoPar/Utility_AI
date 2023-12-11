#include "UtilityAINodeQuerySystem.h"
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/classes/performance.hpp>


using namespace godot;


UtilityAINodeQuerySystem::UtilityAINodeQuerySystem() {
    _time_budget_per_frame = 1000;
    _current_high_priority_query_index = 0;
    _current_regular_query_index = 0;

    _time_allocation_pct_to_high_priority_queries = 0.8f;
    _time_budget_per_frame_high_priority_queries = (uint64_t)(_time_allocation_pct_to_high_priority_queries * ((float)_time_budget_per_frame));
    _time_budget_per_frame_regular_queries = _time_budget_per_frame - _time_budget_per_frame_high_priority_queries;

    _is_performance_counter_initialized = false;
}


UtilityAINodeQuerySystem::~UtilityAINodeQuerySystem() {
    
}

void UtilityAINodeQuerySystem::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_time_budget_per_frame", "time_budget_per_frame"), &UtilityAINodeQuerySystem::set_time_budget_per_frame);
    ClassDB::bind_method(D_METHOD("get_time_budget_per_frame"), &UtilityAINodeQuerySystem::get_time_budget_per_frame);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "time_budget_per_frame", PROPERTY_HINT_RANGE, "1,10000,or_greater"), "set_time_budget_per_frame","get_time_budget_per_frame");
    
    ClassDB::bind_method(D_METHOD("set_time_allocation_pct_to_high_priority_queries", "time_allocation_pct_to_high_priority_queries"), &UtilityAINodeQuerySystem::set_time_allocation_pct_to_high_priority_queries);
    ClassDB::bind_method(D_METHOD("get_time_allocation_pct_to_high_priority_queries"), &UtilityAINodeQuerySystem::get_time_allocation_pct_to_high_priority_queries);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "time_allocation_pct_to_high_priority_queries", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_time_allocation_pct_to_high_priority_queries","get_time_allocation_pct_to_high_priority_queries");
    
    ClassDB::bind_method(D_METHOD("post_query", "search_space", "is_high_priority"), &UtilityAINodeQuerySystem::post_query);
    ClassDB::bind_method(D_METHOD("run_queries"), &UtilityAINodeQuerySystem::run_queries);
    ClassDB::bind_method(D_METHOD("clear_queries"), &UtilityAINodeQuerySystem::clear_queries);
    ClassDB::bind_method(D_METHOD("initialize_performance_counters"), &UtilityAINodeQuerySystem::initialize_performance_counters);
    ClassDB::bind_method(D_METHOD("get_run_queries_time_elapsed_usec"), &UtilityAINodeQuerySystem::get_run_queries_time_elapsed_usec );
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

int  UtilityAINodeQuerySystem::get_run_queries_time_elapsed_usec() const {
    return _run_queries_time_elapsed_usec;
}


// Handling methods.

void UtilityAINodeQuerySystem::initialize_performance_counters() {
    if( _is_performance_counter_initialized ) return;
    Performance* perf = godot::Performance::get_singleton();
    if( perf == nullptr ) return;
    perf->add_custom_monitor("NodeQuerySystem/Run_Queries_Time_usec", Callable(this, "get_run_queries_time_elapsed_usec"));
    _is_performance_counter_initialized = true;
}


void UtilityAINodeQuerySystem::run_queries() {
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    uint64_t frame_time_left = _time_budget_per_frame;
    if( _high_priority_queries.size() == 0 && _regular_queries.size() == 0 ) {
        _run_queries_time_elapsed_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
        return;
    }

    std::vector<int> queries_to_delete;
    if( _high_priority_queries.size() > 0 ) {
        while(true) {
            if( _current_high_priority_query_index >= _high_priority_queries.size() ) {
                _current_high_priority_query_index = 0;
                for( int i = queries_to_delete.size() - 1; i > -1; --i ) {
                    _high_priority_queries.remove_at(queries_to_delete[i]);
                }
                queries_to_delete.clear();
                if( _high_priority_queries.size() == 0 ) {
                    break;
                }
            }

            UtilityAINQSSearchSpaces* current_query = godot::Object::cast_to<UtilityAINQSSearchSpaces>(_high_priority_queries[_current_high_priority_query_index]);
            if( current_query != nullptr ) {
                bool is_completed = current_query->execute_query(10);
                if( is_completed ) {
                    queries_to_delete.push_back(_current_high_priority_query_index);
                }
            }

            ++_current_high_priority_query_index;
            uint64_t time_used = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            if( time_used >= _time_budget_per_frame_high_priority_queries ) {
                break;
            }
        }

        if( queries_to_delete.size() > 0 ) {
            for( int i = queries_to_delete.size() - 1; i > -1; --i ) {
                _high_priority_queries.remove_at(queries_to_delete[i]);
            }
            queries_to_delete.clear();    
        }
    }
    uint64_t regular_query_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    
    if( _regular_queries.size() > 0 ) {
        frame_time_left -= (regular_query_start_time_usec - method_start_time_usec);
        if( frame_time_left <= 0  ) {
            _run_queries_time_elapsed_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
            return; // Too bad, no time left for regular priority queries :(
        }

        while(true) {
            if( _current_regular_query_index >= _regular_queries.size() ) {
                _current_regular_query_index = 0;
                for( int i = queries_to_delete.size() - 1; i > -1; --i ) {
                    _regular_queries.remove_at(queries_to_delete[i]);
                }
                queries_to_delete.clear();
                if( _regular_queries.size() == 0 ) {
                    break;
                }

            }

            UtilityAINQSSearchSpaces* current_query = godot::Object::cast_to<UtilityAINQSSearchSpaces>(_regular_queries[_current_regular_query_index]);
            if( current_query != nullptr ) {
                bool is_completed = current_query->execute_query(10);
                if( is_completed ) {
                    queries_to_delete.push_back(_current_regular_query_index);
                }
            }

            ++_current_regular_query_index;
            uint64_t time_used = godot::Time::get_singleton()->get_ticks_usec() - regular_query_start_time_usec;
            if( time_used >= frame_time_left ) {
                break;
            }        
        }

        for( int i = queries_to_delete.size() - 1; i > -1; --i ) {
            _regular_queries.remove_at(queries_to_delete[i]);
        }    

    }

    _run_queries_time_elapsed_usec = godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec;
}





int UtilityAINodeQuerySystem::post_query( UtilityAINQSSearchSpaces* search_space, bool is_high_priority ) {
    if( search_space == nullptr ) {
        return -1;
    }
    if( is_high_priority ) {
        if( _high_priority_queries.has( search_space ) ){
            return -1;
        }
        search_space->start_query();
        _high_priority_queries.push_back(search_space);
        return 1;
    } else {
        if( _regular_queries.has( search_space ) ){
            return -1;
        }
        search_space->start_query();
        _regular_queries.push_back(search_space);
        return 1;
    }

    return -1;
}


void UtilityAINodeQuerySystem::clear_queries() {
    _high_priority_queries.clear();
    _regular_queries.clear();
}