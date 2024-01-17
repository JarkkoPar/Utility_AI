#ifndef UtilityAINQSSearchSpaces_H_INCLUDED
#define UtilityAINQSSearchSpaces_H_INCLUDED 

//#include "node_query_system.h"
#include "../utility_ai.h"
#include <godot_cpp/classes/node.hpp>
#include "../search_criteria/nqs.h"



namespace godot {

class UtilityAINQSSearchSpaces : public UtilityAI { //NodeQuerySystem {
    GDCLASS(UtilityAINQSSearchSpaces, UtilityAI) //NodeQuerySystem)

private:
    bool                _is_run_in_debug_mode;

    int                 _top_n_to_find;
    unsigned int        _current_criterion_index;
    unsigned int        _current_node_index;
    unsigned int        _current_result_index;
    bool                _is_search_space_fetched;
    bool                _is_preprocessing_completed;
    bool                _is_criteria_handled;
    bool                _is_results_copied;
    bool                _is_query_still_running;
    TypedArray<Node>    _current_query_results;
    PackedFloat64Array  _current_query_result_scores;
    TypedArray<Node>    _query_results;
    PackedFloat64Array  _query_result_scores;
    //float              _query_time_budget_per_frame_sec;
    //uint64_t            _query_time_budget_per_frame_usec;
    uint64_t            _total_query_runtime_usec;
    uint64_t            _current_query_runtime_usec;
    uint64_t            _current_call_runtime_usec;
    uint64_t            _average_call_runtime_usec;
    uint64_t            _search_space_fetch_time_usec;
    uint64_t            _preprocessing_time_usec;
    uint64_t            _completed_signal_time_usec;
    unsigned int        _current_query_node_visits;
    unsigned int        _current_query_call_count;
    unsigned int        _total_query_node_visits;
    unsigned int        _total_query_call_count;
    //float              _total_query_runtime_sec;
    TypedArray<Node>    _search_space;
    PackedFloat64Array  _scores;
    unsigned int        _num_search_space_nodes;
    TypedArray<Node>    _work_in_progress_search_space;
    PackedFloat64Array  _work_in_progress_scores;
    unsigned int        _work_in_progress_num_added_nodes;

    TypedArray<Node>*   _ptr_current_search_space;
    TypedArray<Node>*   _ptr_current_work_in_progress_search_space;
    PackedFloat64Array* _ptr_current_scores;
    PackedFloat64Array* _ptr_current_work_in_progress_scores;

    TypedArray<UtilityAINQSSearchCriteria> _filtering_criteria;

    int                 _nqs_query_index; // Index of the query in the singleton.
    bool                _nqs_query_is_high_priority; 
protected:
    static void _bind_methods();
    virtual void _initialize_search_space(){}
    virtual void _uninitialize_search_space(){}

    /*void apply_criterion(   UtilityAINQSSearchCriteria* criterion, 
                            TypedArray<Node> search_space, 
                            PackedFloat64Array scores, 
                            TypedArray<Node>& result_space, 
                            PackedFloat64Array& result_scores );*/
    bool apply_criterion_with_time_budget( UtilityAINQSSearchCriteria* criterion,
                            uint64_t start_time_usec, 
                            uint64_t time_budget_usec );
    virtual bool preprocess_search_space(uint64_t time_limit_timestamp_usec){_is_preprocessing_completed = true; return true;};
    void place_to_query_results_based_on_score( Node* node, float score );

    unsigned int        _current_preprocessing_node_index;

public:
    UtilityAINQSSearchSpaces();
    ~UtilityAINQSSearchSpaces();
    
    
    // Getters and setters.

    void set_is_run_in_debug_mode(bool is_run_in_debug_mode);
    bool get_is_run_in_debug_mode() const;

    void set_nqs_query_index(int nqs_query_index);
    int  get_nqs_query_index() const;
    
    void set_nqs_query_is_high_priority(bool nqs_query_is_high_priority);
    bool get_nqs_query_is_high_priority() const;

    virtual TypedArray<Node> get_searchspace_nodes() const;
    
    void set_query_results(TypedArray<Node> query_results);
    TypedArray<Node> get_query_results() const;

    void set_query_result_scores(PackedFloat64Array query_result_scores);
    PackedFloat64Array get_query_result_scores() const;

    
    void set_top_n_to_find( int top_n_to_find );
    int  get_top_n_to_find() const;

    void set_average_call_runtime_usec( int average_call_runtime_usec );
    int  get_average_call_runtime_usec() const;

    void set_current_call_runtime_usec( int current_call_runtime_usec );
    int  get_current_call_runtime_usec() const;

    void set_search_space_fetch_time_usec( int search_space_fetch_time_usec );
    int  get_search_space_fetch_time_usec() const;

    void set_total_query_runtime_usec( int total_query_runtime_usec );
    int  get_total_query_runtime_usec() const;

    void set_completed_signal_time_usec( int completed_signal_time_usec );
    int  get_completed_signal_time_usec() const;

    void set_total_query_node_visits( int total_query_node_visits );
    int  get_total_query_node_visits() const;

    void set_total_query_call_count( int total_query_call_count );
    int  get_total_query_call_count() const;

    void set_is_query_still_running( bool is_query_still_running );
    bool get_is_query_still_running() const;
    
    // Handling methods.

    void initialize_search_space();
    void reset_query_variables(); 
    
    virtual void start_query();
    virtual bool execute_query(uint64_t time_budget_usec = 0 );

    //void apply_criterion( UtilityAISearchCriteria* criteria, TypedArray<Node> search_space, TypedArray<float> current_scores, TypedArray<Node>& result_space, TypedArray<float>& result_scores );
    
    // Godot virtuals.
    void _ready();
    void _exit_tree();
};

}


#endif 
