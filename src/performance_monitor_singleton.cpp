#include "performance_monitor_singleton.h"
#include <godot_cpp/classes/performance.hpp>

using namespace godot;


UtilityAIPerformanceMonitorSingleton* UtilityAIPerformanceMonitorSingleton::_singleton = nullptr;


UtilityAIPerformanceMonitorSingleton::UtilityAIPerformanceMonitorSingleton() {
    set_is_active(false);
    _total_time_elapsed_ai_agents_usec = 0;
    _total_time_elapsed_behaviour_trees_usec = 0;
    _current_total_time_elapsed_ai_agents_usec = 0;
    _current_total_time_elapsed_behaviour_trees_usec = 0;
    _singleton = this;
}


UtilityAIPerformanceMonitorSingleton::~UtilityAIPerformanceMonitorSingleton() {

}

void UtilityAIPerformanceMonitorSingleton::_bind_methods() {

    ClassDB::bind_method(D_METHOD("increment_total_time_elapsed_ai_agents_usec", "time_usec"), &UtilityAIPerformanceMonitorSingleton::increment_total_time_elapsed_ai_agents_usec);
    ClassDB::bind_method(D_METHOD("increment_total_time_elapsed_behaviour_trees_usec", "time_usec"), &UtilityAIPerformanceMonitorSingleton::increment_total_time_elapsed_behaviour_trees_usec);
    ClassDB::bind_method(D_METHOD("increment_total_time_elapsed_state_trees_usec", "time_usec"), &UtilityAIPerformanceMonitorSingleton::increment_total_time_elapsed_state_trees_usec);

    ClassDB::bind_method(D_METHOD("initialize_performance_counters"), &UtilityAIPerformanceMonitorSingleton::initialize_performance_counters);
    ClassDB::bind_method(D_METHOD("update_performance_counters"), &UtilityAIPerformanceMonitorSingleton::update_performance_counters);

    ClassDB::bind_method(D_METHOD("get_total_time_elapsed_ai_agents_usec"), &UtilityAIPerformanceMonitorSingleton::get_total_time_elapsed_ai_agents_usec);
    ClassDB::bind_method(D_METHOD("get_total_time_elapsed_behaviour_trees_usec"), &UtilityAIPerformanceMonitorSingleton::get_total_time_elapsed_behaviour_trees_usec);
    ClassDB::bind_method(D_METHOD("get_total_time_elapsed_state_trees_usec"), &UtilityAIPerformanceMonitorSingleton::get_total_time_elapsed_state_trees_usec);
}

// Getters and setters.


int  UtilityAIPerformanceMonitorSingleton::get_current_total_time_elapsed_ai_agents_usec() const {
    return _current_total_time_elapsed_ai_agents_usec;
}


int  UtilityAIPerformanceMonitorSingleton::get_current_total_time_elapsed_behaviour_trees_usec() const {
    return _current_total_time_elapsed_behaviour_trees_usec;
}


int  UtilityAIPerformanceMonitorSingleton::get_current_total_time_elapsed_state_trees_usec() const {
    return _current_total_time_elapsed_state_trees_usec;
}


int  UtilityAIPerformanceMonitorSingleton::get_total_time_elapsed_ai_agents_usec() const {
    return _total_time_elapsed_ai_agents_usec;
}


int  UtilityAIPerformanceMonitorSingleton::get_total_time_elapsed_behaviour_trees_usec() const {
    return _total_time_elapsed_behaviour_trees_usec;
}


int  UtilityAIPerformanceMonitorSingleton::get_total_time_elapsed_state_trees_usec() const {
    return _total_time_elapsed_state_trees_usec;
}


// Handling methods.

void UtilityAIPerformanceMonitorSingleton::increment_total_time_elapsed_ai_agents_usec( uint64_t time_usec ) {
    _current_total_time_elapsed_ai_agents_usec += time_usec;
}


void UtilityAIPerformanceMonitorSingleton::increment_total_time_elapsed_behaviour_trees_usec( uint64_t time_usec ) {
    _current_total_time_elapsed_behaviour_trees_usec += time_usec;
}


void UtilityAIPerformanceMonitorSingleton::increment_total_time_elapsed_state_trees_usec( uint64_t time_usec ) {
    _current_total_time_elapsed_state_trees_usec += time_usec;
}


void UtilityAIPerformanceMonitorSingleton::initialize_performance_counters() {
    if( _is_performance_counter_initialized ) return;
    Performance* perf = godot::Performance::get_singleton();
    if( perf == nullptr ) return;
    perf->add_custom_monitor("UtilityAI/AI Agent evaluate options time usec", Callable(this, "get_total_time_elapsed_ai_agents_usec"));
    perf->add_custom_monitor("UtilityAI/Behaviour Tree tick time usec", Callable(this, "get_total_time_elapsed_behaviour_trees_usec"));
    perf->add_custom_monitor("UtilityAI/State Tree tick time usec", Callable(this, "get_total_time_elapsed_state_trees_usec"));
    _is_performance_counter_initialized = true;
    set_is_active(true);
}


void UtilityAIPerformanceMonitorSingleton::update_performance_counters() {
    _total_time_elapsed_ai_agents_usec = _current_total_time_elapsed_ai_agents_usec;
    _total_time_elapsed_behaviour_trees_usec = _current_total_time_elapsed_behaviour_trees_usec;
    _total_time_elapsed_state_trees_usec = _current_total_time_elapsed_state_trees_usec;
    _current_total_time_elapsed_ai_agents_usec = 0;
    _current_total_time_elapsed_behaviour_trees_usec = 0;
    _current_total_time_elapsed_state_trees_usec = 0;
}