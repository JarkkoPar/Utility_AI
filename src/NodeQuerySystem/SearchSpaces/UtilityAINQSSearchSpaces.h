#ifndef UtilityAINQSSearchSpaces_H_INCLUDED
#define UtilityAINQSSearchSpaces_H_INCLUDED 

#include "UtilityAINodeQuerySystem.h"
#include <godot_cpp/classes/node.hpp>
#include "../SearchCriteria/UtilityAISearchCriteria.h"



namespace godot {

class UtilityAINQSSearchSpaces : public UtilityAINodeQuerySystem {
    GDCLASS(UtilityAINQSSearchSpaces, UtilityAINodeQuerySystem)

private:
    int                 _top_n_to_find;
    TypedArray<Node>    _query_results;

    TypedArray<UtilityAISearchCriteria> _filtering_criteria;

protected:
    static void _bind_methods();

public:
    UtilityAINQSSearchSpaces();
    ~UtilityAINQSSearchSpaces();
    
    
    // Getters and setters.

    virtual TypedArray<Node> get_searchspace_nodes() const;
    
    void set_query_results(TypedArray<Node> query_results);
    TypedArray<Node> get_query_results() const;
    
    void set_top_n_to_find( int top_n_to_find );
    int  get_top_n_to_find() const;

    // Handling methods.

    virtual void execute_query();

    //void apply_criterion( UtilityAISearchCriteria* criteria, TypedArray<Node> search_space, TypedArray<double> current_scores, TypedArray<Node>& result_space, TypedArray<double>& result_scores );
    
    // Godot virtuals.
    void _ready();
};

}


#endif 
