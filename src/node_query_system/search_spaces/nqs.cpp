#include "nqs.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include "../node_query_system.h"

using namespace godot;


UtilityAINQSSearchSpaces::UtilityAINQSSearchSpaces() {
    _top_n_to_find = 1;
    _nqs_query_index = -1;
    _nqs_query_is_high_priority = true;
    _is_query_still_running = false;
    _is_search_space_fetched = false;
    _is_criteria_handled = false;
    _is_results_copied = false;
    _current_criterion_index = 0;
    _total_query_runtime_usec = 0;
    _work_in_progress_num_added_nodes = 0;
    _total_query_call_count = 0;
    _total_query_node_visits = 0;
    _current_query_call_count = 0;
    _current_query_node_visits = 0;
    _current_query_runtime_usec = 0;
    _average_call_runtime_usec = 0;
    _current_call_runtime_usec = 0;
    _search_space_fetch_time_usec = 0;
    _preprocessing_time_usec = 0;
    _completed_signal_time_usec = 0;
    _is_run_in_debug_mode = false;
}


UtilityAINQSSearchSpaces::~UtilityAINQSSearchSpaces() {
}


void UtilityAINQSSearchSpaces::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_top_n_to_find", "top_n_to_find"), &UtilityAINQSSearchSpaces::set_top_n_to_find);
    ClassDB::bind_method(D_METHOD("get_top_n_to_find"), &UtilityAINQSSearchSpaces::get_top_n_to_find);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "top_n_to_find", PROPERTY_HINT_RANGE, "1,32,or_greater"), "set_top_n_to_find","get_top_n_to_find");
    
    ClassDB::bind_method(D_METHOD("set_query_results", "query_results"), &UtilityAINQSSearchSpaces::set_query_results);
    ClassDB::bind_method(D_METHOD("get_query_results"), &UtilityAINQSSearchSpaces::get_query_results);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "query_results", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Node")), "set_query_results","get_query_results");

    ClassDB::bind_method(D_METHOD("set_query_result_scores", "query_result_scores"), &UtilityAINQSSearchSpaces::set_query_result_scores);
    ClassDB::bind_method(D_METHOD("get_query_result_scores"), &UtilityAINQSSearchSpaces::get_query_result_scores);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "query_result_scores", PROPERTY_HINT_NONE), "set_query_result_scores","get_query_result_scores");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_is_run_in_debug_mode", "is_run_in_debug_mode"), &UtilityAINQSSearchSpaces::set_is_run_in_debug_mode);
    ClassDB::bind_method(D_METHOD("get_is_run_in_debug_mode"), &UtilityAINQSSearchSpaces::get_is_run_in_debug_mode);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_run_in_debug_mode", PROPERTY_HINT_NONE), "set_is_run_in_debug_mode","get_is_run_in_debug_mode");

    ClassDB::bind_method(D_METHOD("set_is_query_still_running", "is_query_still_running"), &UtilityAINQSSearchSpaces::set_is_query_still_running);
    ClassDB::bind_method(D_METHOD("get_is_query_still_running"), &UtilityAINQSSearchSpaces::get_is_query_still_running);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_query_still_running", PROPERTY_HINT_NONE), "set_is_query_still_running","get_is_query_still_running");

    ClassDB::bind_method(D_METHOD("set_average_call_runtime_usec", "average_call_runtime_usec"), &UtilityAINQSSearchSpaces::set_average_call_runtime_usec);
    ClassDB::bind_method(D_METHOD("get_average_call_runtime_usec"), &UtilityAINQSSearchSpaces::get_average_call_runtime_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "average_call_runtime_usec", PROPERTY_HINT_NONE), "set_average_call_runtime_usec","get_average_call_runtime_usec");

    ClassDB::bind_method(D_METHOD("set_search_space_fetch_time_usec", "average_call_runtime_usec"), &UtilityAINQSSearchSpaces::set_search_space_fetch_time_usec);
    ClassDB::bind_method(D_METHOD("get_search_space_fetch_time_usec"), &UtilityAINQSSearchSpaces::get_search_space_fetch_time_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "search_space_fetch_time_usec", PROPERTY_HINT_NONE), "set_search_space_fetch_time_usec","get_search_space_fetch_time_usec");

    ClassDB::bind_method(D_METHOD("set_total_query_runtime_usec", "total_query_runtime_usec"), &UtilityAINQSSearchSpaces::set_total_query_runtime_usec);
    ClassDB::bind_method(D_METHOD("get_total_query_runtime_usec"), &UtilityAINQSSearchSpaces::get_total_query_runtime_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_query_runtime_usec", PROPERTY_HINT_NONE), "set_total_query_runtime_usec","get_total_query_runtime_usec");

    ClassDB::bind_method(D_METHOD("set_completed_signal_time_usec", "total_query_runtime_usec"), &UtilityAINQSSearchSpaces::set_completed_signal_time_usec);
    ClassDB::bind_method(D_METHOD("get_completed_signal_time_usec"), &UtilityAINQSSearchSpaces::get_completed_signal_time_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "completed_signal_time_usec", PROPERTY_HINT_NONE), "set_completed_signal_time_usec","get_completed_signal_time_usec");

    ClassDB::bind_method(D_METHOD("set_total_query_node_visits", "total_query_node_visits"), &UtilityAINQSSearchSpaces::set_total_query_node_visits);
    ClassDB::bind_method(D_METHOD("get_total_query_node_visits"), &UtilityAINQSSearchSpaces::get_total_query_node_visits);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_query_node_visits", PROPERTY_HINT_NONE), "set_total_query_node_visits","get_total_query_node_visits");

    ClassDB::bind_method(D_METHOD("set_total_query_call_count", "total_query_call_count"), &UtilityAINQSSearchSpaces::set_total_query_call_count);
    ClassDB::bind_method(D_METHOD("get_total_query_call_count"), &UtilityAINQSSearchSpaces::get_total_query_call_count);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "total_query_call_count", PROPERTY_HINT_NONE), "set_total_query_call_count","get_total_query_call_count");

    //PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::FLOAT, PROPERTY_HINT_NONE)
    ClassDB::bind_method(D_METHOD("initialize_search_space"), &UtilityAINQSSearchSpaces::initialize_search_space);
    ClassDB::bind_method(D_METHOD("execute_query", "time_budget_usec"), &UtilityAINQSSearchSpaces::execute_query);

    ADD_SIGNAL(MethodInfo("query_completed", PropertyInfo(Variant::OBJECT, "search_space")));
}


void UtilityAINQSSearchSpaces::_ready() {
    //if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    initialize_search_space(); // Maybe not really needed? We'll see.
    /**
    // Find all the boolean filtering criterias, as they will be run first.
    _filtering_criteria.clear();
    for( int i = 0; i < get_child_count(); ++i ) {
        UtilityAISearchCriteria* criterion = godot::Object::cast_to<UtilityAISearchCriteria>(get_child(i));
        if( criterion == nullptr ) {
            continue;
        }
        if( criterion->get_is_filtered() && !criterion->get_is_scored() ) {
            _filtering_criteria.push_back(criterion);
        }
    }//endfor criteria
    */
}


void UtilityAINQSSearchSpaces::_exit_tree() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    _uninitialize_search_space();
    // If we don't remove this search space from the singleton, it'll cause a memory leak.
    UtilityAINodeQuerySystem* nqs = godot::Object::cast_to<UtilityAINodeQuerySystem>(Engine::get_singleton()->get_singleton("NodeQuerySystem"));
    if( nqs == nullptr ) return;
    nqs->stop_query(this);

}


// Getters and setters.

void UtilityAINQSSearchSpaces::set_is_run_in_debug_mode(bool is_run_in_debug_mode) {
    _is_run_in_debug_mode = is_run_in_debug_mode;
}


bool UtilityAINQSSearchSpaces::get_is_run_in_debug_mode() const {
    return _is_run_in_debug_mode;
}


void UtilityAINQSSearchSpaces::set_nqs_query_index(int nqs_query_index) {
    _nqs_query_index = nqs_query_index;
}


int  UtilityAINQSSearchSpaces::get_nqs_query_index() const {
    return _nqs_query_index;
}

void UtilityAINQSSearchSpaces::set_nqs_query_is_high_priority(bool nqs_query_is_high_priority) {
    _nqs_query_is_high_priority = nqs_query_is_high_priority;
}


bool  UtilityAINQSSearchSpaces::get_nqs_query_is_high_priority() const {
    return _nqs_query_is_high_priority;
}


TypedArray<Node> UtilityAINQSSearchSpaces::get_searchspace_nodes() const {
    TypedArray<Node> emptyarray;
    return emptyarray;
}


void UtilityAINQSSearchSpaces::set_query_results(TypedArray<Node> query_results) {
    _query_results = query_results;
}


TypedArray<Node> UtilityAINQSSearchSpaces::get_query_results() const {
    return _query_results;
}


void UtilityAINQSSearchSpaces::set_query_result_scores(PackedFloat64Array query_result_scores) {
    _query_result_scores = query_result_scores;
}


PackedFloat64Array UtilityAINQSSearchSpaces::get_query_result_scores() const {
    return _query_result_scores;
}


void UtilityAINQSSearchSpaces::set_top_n_to_find( int top_n_to_find ) {
    _top_n_to_find = top_n_to_find;
}


int  UtilityAINQSSearchSpaces::get_top_n_to_find() const {
    return _top_n_to_find;
}

void UtilityAINQSSearchSpaces::set_current_call_runtime_usec( int current_call_runtime_usec ) {
    _current_call_runtime_usec = current_call_runtime_usec;
}
int  UtilityAINQSSearchSpaces::get_current_call_runtime_usec() const {
    return _current_call_runtime_usec;
}

void UtilityAINQSSearchSpaces::set_search_space_fetch_time_usec( int search_space_fetch_time_usec ) {
    _search_space_fetch_time_usec = search_space_fetch_time_usec;
}

int  UtilityAINQSSearchSpaces::get_search_space_fetch_time_usec() const {
    return _search_space_fetch_time_usec;
}

void UtilityAINQSSearchSpaces::set_average_call_runtime_usec( int average_call_runtime_usec ) {
    _average_call_runtime_usec = average_call_runtime_usec;
}

int  UtilityAINQSSearchSpaces::get_average_call_runtime_usec() const {
    return _average_call_runtime_usec;
}


void UtilityAINQSSearchSpaces::set_total_query_runtime_usec( int total_query_runtime_usec ) {
    _total_query_runtime_usec = total_query_runtime_usec;
}


int  UtilityAINQSSearchSpaces::get_total_query_runtime_usec() const {
    return _total_query_runtime_usec;
}


void UtilityAINQSSearchSpaces::set_total_query_node_visits( int total_query_node_visits ) {
    _total_query_node_visits = total_query_node_visits;
}


int  UtilityAINQSSearchSpaces::get_total_query_node_visits() const {
    return _total_query_node_visits;
}


void UtilityAINQSSearchSpaces::set_total_query_call_count( int total_query_call_count ) {
    _total_query_call_count = total_query_call_count;
}


int  UtilityAINQSSearchSpaces::get_total_query_call_count() const {
    return _total_query_call_count;
}

void UtilityAINQSSearchSpaces::set_is_query_still_running( bool is_query_still_running ) {
    _is_query_still_running = is_query_still_running;
}
bool UtilityAINQSSearchSpaces::get_is_query_still_running() const {
    return _is_query_still_running;
}


void UtilityAINQSSearchSpaces::set_completed_signal_time_usec( int completed_signal_time_usec ) {
    _completed_signal_time_usec = completed_signal_time_usec;
}

int  UtilityAINQSSearchSpaces::get_completed_signal_time_usec() const {
    return _completed_signal_time_usec;
}


// Handling methods.

void UtilityAINQSSearchSpaces::initialize_search_space() {
    _initialize_search_space();
}


void UtilityAINQSSearchSpaces::reset_query_variables() {
    // Query was not running already, so initialize a new one.
    _current_query_runtime_usec = 0;
    _current_query_node_visits = 0;
    _current_query_call_count = 0;
    _average_call_runtime_usec = 0;
    _current_call_runtime_usec = 0;
    _search_space_fetch_time_usec = 0;
    _current_criterion_index = 0;
    _current_node_index = 0;
    _current_result_index = 0;
    _work_in_progress_num_added_nodes = 0;

    _preprocessing_time_usec = 0;
    _current_preprocessing_node_index = 0;

    _is_search_space_fetched = false; 
    _is_preprocessing_completed = false;
    _is_criteria_handled = false;
    _is_results_copied = false;

    _is_query_still_running = true; // Set the query as running.
}


void UtilityAINQSSearchSpaces::start_query() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( get_child_count() < 1 ) {
        WARN_PRINT("UtilityAINodeQuerySystem::start_query() - No search criteria nodes added.");
        return;
    }
    reset_query_variables();
}


bool UtilityAINQSSearchSpaces::execute_query(uint64_t time_budget_usec) {
    uint64_t method_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    uint64_t method_time_limit_timestamp_usec = method_start_time_usec + time_budget_usec;
    uint64_t time_budget_remaining_usec = time_budget_usec;

    if( !get_is_active() ) return true;
    if( Engine::get_singleton()->is_editor_hint() ) return true;
    if( get_child_count() < 1 ) {
        WARN_PRINT("UtilityAINodeQuerySystem::execute_query() - No search criteria nodes added.");
        return true;
    }

    if( !_is_query_still_running ) {
        reset_query_variables();
    }//endif query is not running
    ++_current_query_call_count;

    if( !_is_search_space_fetched ) {
        // Get the search space nodes and set the score to 1.0 for all of them.
        _search_space = get_searchspace_nodes();
        _num_search_space_nodes = _search_space.size();
        _scores.resize(_num_search_space_nodes);
        _scores.fill(1.0);

        // Create the work-in-progress search space we will be swapping with.
        _work_in_progress_search_space = _search_space.duplicate();
        _work_in_progress_scores = _scores.duplicate();
        _work_in_progress_num_added_nodes = 0;

        _ptr_current_search_space = &_search_space;
        _ptr_current_scores = &_scores;

        _ptr_current_work_in_progress_search_space = &_work_in_progress_search_space;
        _ptr_current_work_in_progress_scores = &_work_in_progress_scores;
        
        _is_search_space_fetched = true;

        uint64_t search_space_fetch_end_timestamp_usec = godot::Time::get_singleton()->get_ticks_usec();
        _search_space_fetch_time_usec = search_space_fetch_end_timestamp_usec - method_start_time_usec;
        if( time_budget_usec > 0 && search_space_fetch_end_timestamp_usec >= method_time_limit_timestamp_usec ) {
            // Update the debug counters before exiting.
            _current_call_runtime_usec = _search_space_fetch_time_usec; 
            _average_call_runtime_usec = _average_call_runtime_usec * 0.5 + 0.5 * _current_call_runtime_usec;
            _current_query_runtime_usec += _current_call_runtime_usec; 
            return false; // Search space fetching used the time budget.
        }
        time_budget_remaining_usec -= _search_space_fetch_time_usec;
        
    }//endif is searchspace fetched

    // Do any preprocessing that's needed.
    if( !_is_preprocessing_completed ) {
        uint64_t preprocessing_start_timestamp_usec = godot::Time::get_singleton()->get_ticks_usec();
        _is_preprocessing_completed = preprocess_search_space(method_time_limit_timestamp_usec);
        uint64_t preprocessing_end_timestamp_usec = godot::Time::get_singleton()->get_ticks_usec();
        _preprocessing_time_usec += (preprocessing_end_timestamp_usec - preprocessing_start_timestamp_usec);
        time_budget_remaining_usec -= _preprocessing_time_usec;
        //if( time_budget_usec > 0 && time_budget_remaining_usec <= 0) {
        if( time_budget_usec > 0 && preprocessing_end_timestamp_usec >= method_time_limit_timestamp_usec ) {
            // Update the debug counters before exiting.
            _current_call_runtime_usec = preprocessing_end_timestamp_usec - method_start_time_usec;//godot::Time::get_singleton()->get_ticks_usec(); 
            _average_call_runtime_usec = _average_call_runtime_usec * 0.5 + 0.5 * _current_call_runtime_usec;
            _current_query_runtime_usec += _current_call_runtime_usec; 
            
            return false; // Preprocessing used the time budget.
        }
    }

    // Handle the criteria.
    if( !_is_criteria_handled ) {
        while( _current_criterion_index < get_child_count() ) {
            UtilityAINQSSearchCriteria* criterion = godot::Object::cast_to<UtilityAINQSSearchCriteria>(get_child(_current_criterion_index));
            if( criterion == nullptr ){
                ++_current_criterion_index;
                continue;
            } 
            if( !criterion->get_is_active() ){
                ++_current_criterion_index;
                continue;
            } 
            bool is_criterion_complete = apply_criterion_with_time_budget(criterion,
                                                                method_start_time_usec,
                                                                time_budget_remaining_usec );
            if( !is_criterion_complete) {
                // Note: the runtime is already updated in the apply_criterion_with_time_budget() method.
                return false; // The criterion did not complete, so it timed out.
            }
            ++_current_criterion_index;
        }//endwhile criterions left to process
        _is_criteria_handled = true;
        _current_query_results.clear();
        _current_query_result_scores.clear();
    }//endif is criteria handled
    uint64_t copy_start_time_usec = godot::Time::get_singleton()->get_ticks_usec();
    //time_budget_remaining_usec = time_budget_usec - (copy_start_time_usec - method_start_time_usec);
    uint64_t copy_end_time_usec = copy_start_time_usec + time_budget_usec - (copy_start_time_usec - method_start_time_usec);

    // Put all the remaining scores to the search results in order.
    if( !_is_results_copied ) {
        while( _current_result_index < _num_search_space_nodes ) {
            uint64_t current_time_usec = godot::Time::get_singleton()->get_ticks_usec();
            if( current_time_usec >= copy_end_time_usec) {
                _current_call_runtime_usec = (current_time_usec - method_start_time_usec);
                _average_call_runtime_usec = _average_call_runtime_usec * 0.5 + 0.5 * _current_call_runtime_usec;
                _current_query_runtime_usec += _current_call_runtime_usec; 
                return false;
            }

            Node* node = godot::Object::cast_to<Node>((*_ptr_current_search_space)[_current_result_index]);
            place_to_query_results_based_on_score(node, (*_ptr_current_scores)[_current_result_index]);
            ++_current_result_index;
        }
        _query_results = _current_query_results;
        _query_result_scores = _current_query_result_scores;
        _is_results_copied = true;
    }//endif results are copied
    

    // Clear everything to be ready for the next query.
    _current_criterion_index = 0;
    _current_node_index = 0;
    _current_result_index = 0;
    _work_in_progress_num_added_nodes = 0;
    _num_search_space_nodes = 0;
    _is_query_still_running = false;
    _total_query_call_count = _current_query_call_count;
    _total_query_node_visits = _current_query_node_visits;

    // Emit the signal that this query completed.
    uint64_t signal_start_timestamp = godot::Time::get_singleton()->get_ticks_usec();
    emit_signal("query_completed", this);
    _completed_signal_time_usec = godot::Time::get_singleton()->get_ticks_usec() - signal_start_timestamp;

    // All the criterions are processed and results sorted. Store the total time used for processing.
    _current_call_runtime_usec = (godot::Time::get_singleton()->get_ticks_usec() - method_start_time_usec);
    _average_call_runtime_usec = _average_call_runtime_usec * 0.5 + 0.5 * _current_call_runtime_usec;
    _current_query_runtime_usec += _current_call_runtime_usec; 
    _total_query_runtime_usec = _current_query_runtime_usec;

    // The query is done.
    return true;
}


bool UtilityAINQSSearchSpaces::apply_criterion_with_time_budget( UtilityAINQSSearchCriteria* criterion, 
                                                                 uint64_t start_time_usec,
                                                                 uint64_t time_budget_usec ) {
    uint64_t end_time_usec = start_time_usec + time_budget_usec;
    //uint64_t current_time_usec = 0;
    while( _current_node_index < _num_search_space_nodes ) {
        uint64_t current_time_usec = godot::Time::get_singleton()->get_ticks_usec();
        if( time_budget_usec > 0 ) {
            if( current_time_usec >= end_time_usec ) {
                _current_call_runtime_usec = current_time_usec - start_time_usec;
                _average_call_runtime_usec = _average_call_runtime_usec * 0.5 + 0.5 * _current_call_runtime_usec;
                return false;
            }//endif time budget reached.
        }//endif timebudget is applied

        Node* node = godot::Object::cast_to<Node>((*_ptr_current_search_space)[_current_node_index]);
        if( node == nullptr ){
            ++_current_node_index;
            continue;
        } 
        bool filter_out = false;
        float score = 1.0f;
        float previous_score = 1.0f;
        if( _current_node_index < (*_ptr_current_scores).size() ) {
            previous_score = (*_ptr_current_scores)[_current_node_index];
        }
        ++_current_query_node_visits;
        criterion->apply_criterion(node, filter_out, score );
        if( !filter_out ) {
            (*_ptr_current_work_in_progress_search_space)[_work_in_progress_num_added_nodes] = node;
            (*_ptr_current_work_in_progress_scores)[_work_in_progress_num_added_nodes] = (previous_score * score);
            ++_work_in_progress_num_added_nodes;
        } 
        if( _is_run_in_debug_mode ) {
            node->set("is_filtered", filter_out );
            node->set("score", (previous_score * score) );
        }

        // Move to the next node.
        ++_current_node_index;
    }//endwhile nodes

    TypedArray<Node>* temparray = _ptr_current_search_space;
    PackedFloat64Array* tempscores = _ptr_current_scores;
    _ptr_current_search_space = _ptr_current_work_in_progress_search_space;
    _ptr_current_scores = _ptr_current_work_in_progress_scores;

    _ptr_current_work_in_progress_search_space = temparray;
    _ptr_current_work_in_progress_scores = tempscores;

    _num_search_space_nodes = _work_in_progress_num_added_nodes;

    _current_node_index = 0;
    _work_in_progress_num_added_nodes = 0;

    // All done! 
    return true; 
}


/*
void UtilityAINQSSearchSpaces::apply_criterion( UtilityAINQSSearchCriteria* criterion, TypedArray<Node> search_space, PackedFloat64Array scores, TypedArray<Node>& result_space, PackedFloat64Array& result_scores ) {
    TypedArray<Node> result_space_after_application;
    PackedFloat64Array result_scores_after_application;

    bool filter_out = false;
    float score = 0.0;
    _current_node_index = 0;
    for( int i = 0; i < search_space.size(); ++i ) {
        Node* node = godot::Object::cast_to<Node>(search_space[i]);
        if( node == nullptr ) continue;
        float previous_score = 1.0;
        if( i < scores.size() ) {
            previous_score = scores[i];
        }
        
        criterion->apply_criterion(node, filter_out, score );
        if( filter_out ) continue;

        result_space_after_application.push_back(node);
        result_scores_after_application.push_back(previous_score * score);
    }//endfor search space nodes

    result_space = result_space_after_application;
    result_scores = result_scores_after_application;
}
*/

void UtilityAINQSSearchSpaces::place_to_query_results_based_on_score( Node* node, float score ) {
    int num_entries = _current_query_result_scores.size();
    if( num_entries == 0 ) {
        _current_query_results.push_back(node);
        _current_query_result_scores.push_back(score);
        return;
    } else if( num_entries == _top_n_to_find ) {
        if( score < _current_query_result_scores[_top_n_to_find - 1]) return; // Worse than the worst on the list.
    }
    
    int i = 0;//_current_query_result_scores.bsearch(score); 
    while( i < num_entries && _current_query_result_scores[i] >= score ) {
        ++i;
    }

    if( i < num_entries ) {
        _current_query_results.insert(i, node);
        _current_query_result_scores.insert(i, score);
        if( num_entries + 1 > _top_n_to_find ) {
            //_current_query_result_scores = 
            _current_query_result_scores.remove_at(_top_n_to_find);//.slice(0, _top_n_to_find-1);//.remove_at(_top_n_to_find);
            //_current_query_results = 
            _current_query_results.remove_at(_top_n_to_find);//(0, _top_n_to_find-1); //.remove_at(_top_n_to_find);
        }
        return;
    }
    if( i < _top_n_to_find ) {
        _current_query_results.push_back(node);
        _current_query_result_scores.push_back(score);
    }
}

