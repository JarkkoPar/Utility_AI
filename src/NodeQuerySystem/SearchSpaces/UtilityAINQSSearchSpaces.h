#ifndef UtilityAINQSSearchSpaces_H_INCLUDED
#define UtilityAINQSSearchSpaces_H_INCLUDED 

//#include "UtilityAINodeQuerySystem.h"
#include "../UtilityAI.h"
#include <godot_cpp/classes/node.hpp>
#include "../SearchCriteria/UtilityAINQSSearchCriteria.h"



namespace godot {

class UtilityAINQSSearchSpaces : public UtilityAI { //NodeQuerySystem {
    GDCLASS(UtilityAINQSSearchSpaces, UtilityAI) //NodeQuerySystem)

private:
    int                 _top_n_to_find;
    TypedArray<Node>    _query_results;
    PackedFloat64Array  _query_result_scores;

    TypedArray<UtilityAINQSSearchCriteria> _filtering_criteria;

protected:
    static void _bind_methods();
    virtual void _initialize_search_space(){}

    void apply_criterion( UtilityAINQSSearchCriteria* criterion, TypedArray<Node> search_space, PackedFloat64Array scores, TypedArray<Node>& result_space, PackedFloat64Array& result_scores );
    void place_to_query_results_based_on_score( Node* node, double score );
public:
    UtilityAINQSSearchSpaces();
    ~UtilityAINQSSearchSpaces();
    
    
    // Getters and setters.

    virtual TypedArray<Node> get_searchspace_nodes() const;
    
    void set_query_results(TypedArray<Node> query_results);
    TypedArray<Node> get_query_results() const;

    void set_query_result_scores(PackedFloat64Array query_result_scores);
    PackedFloat64Array get_query_result_scores() const;

    
    void set_top_n_to_find( int top_n_to_find );
    int  get_top_n_to_find() const;

    // Handling methods.

    void initialize_search_space();

    virtual void execute_query();

    //void apply_criterion( UtilityAISearchCriteria* criteria, TypedArray<Node> search_space, TypedArray<double> current_scores, TypedArray<Node>& result_space, TypedArray<double>& result_scores );
    
    // Godot virtuals.
    void _ready();
};

}


#endif 
