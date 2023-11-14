#include "UtilityAINQSSearchSpaces.h"
#include <godot_cpp/classes/engine.hpp>


using namespace godot;


UtilityAINQSSearchSpaces::UtilityAINQSSearchSpaces() {
    _top_n_to_find = 1;
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
    //PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::FLOAT, PROPERTY_HINT_NONE)
    ClassDB::bind_method(D_METHOD("initialize_search_space"), &UtilityAINQSSearchSpaces::initialize_search_space);
    ClassDB::bind_method(D_METHOD("execute_query"), &UtilityAINQSSearchSpaces::execute_query);
}


void UtilityAINQSSearchSpaces::_ready() {
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


// Getters and setters.

TypedArray<Node> UtilityAINQSSearchSpaces::get_searchspace_nodes() const {
    return nullptr;
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


// Handling methods.

void UtilityAINQSSearchSpaces::initialize_search_space() {
    _initialize_search_space();
}


void UtilityAINQSSearchSpaces::execute_query() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    if( get_child_count() < 1 ) {
        WARN_PRINT("UtilityAINodeQuerySystem::execute_query() - No search criteria nodes added.");
        return;
    }
    
    _query_results.clear();
    _query_result_scores.clear();
    
    // Use the search criterias to narrow down the search space with
    // each applied criterion.
    bool is_filtered_out = false;
    double score = 0.0;
    TypedArray<Node> search_space = get_searchspace_nodes();
    PackedFloat64Array scores;
    for( int c = 0; c < get_child_count(); ++c ) {
        UtilityAINQSSearchCriteria* criterion = godot::Object::cast_to<UtilityAINQSSearchCriteria>(get_child(c));
        if( criterion == nullptr ) continue;
        apply_criterion(criterion, search_space, scores, search_space, scores );
    }
    // Put all the remaining scores to the serach results in order.
    for( int n = 0; n < search_space.size(); ++n ) {
        Node* node = godot::Object::cast_to<Node>(search_space[n]);
        place_to_query_results_based_on_score(node, scores[n]);
    }
    /**
    // The compulsory naive implementation of the search criteria application.
    double total_score = 0.0;
    TypedArray<Node> search_space = get_searchspace_nodes();
    for( int ss = 0; ss < search_space.size(); ++ss ) {
        Node* node = godot::Object::cast_to<Node>(search_space[ss]);
        if( node == nullptr ) continue;
            
        total_score = 0.0;
        for( int c = 0; c < get_child_count(); ++c ) {
            UtilityAINQSSearchCriteria* criterion = godot::Object::cast_to<UtilityAINQSSearchCriteria>(get_child(c));
            if( criterion == nullptr ) continue;
            
            criterion->apply_criterion(node, is_filtered_out, score);           
            total_score += score;
            if( is_filtered_out ) break;


        }//endfor search criteria
        if( !is_filtered_out ) {
            place_to_query_results_based_on_score(node, score);
        }
    }//endfor nodes in the search space
    /**/

}


void UtilityAINQSSearchSpaces::apply_criterion( UtilityAINQSSearchCriteria* criterion, TypedArray<Node> search_space, PackedFloat64Array scores, TypedArray<Node>& result_space, PackedFloat64Array& result_scores ) {
    TypedArray<Node> result_space_after_application;
    PackedFloat64Array result_scores_after_application;

    bool filter_out = false;
    double score = 0.0;
    for( int i = 0; i < search_space.size(); ++i ) {
        Node* node = godot::Object::cast_to<Node>(search_space[i]);
        if( node == nullptr ) continue;
        double previous_score = 1.0;
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


void UtilityAINQSSearchSpaces::place_to_query_results_based_on_score( Node* node, double score ) {
    if( _query_result_scores.size() == 0 ) {
        _query_results.push_back(node);
        _query_result_scores.push_back(score);
        return;
    } else if( _query_result_scores.size() == _top_n_to_find ) {
        if( score < _query_result_scores[_top_n_to_find - 1]) return; // Worse than the worst on the list.
    }
    
    int i = 0; 
    while( i < _query_result_scores.size() && _query_result_scores[i] > score ) {
        ++i;
    }

    if( i < _query_result_scores.size() ) {
        _query_results.insert(i, node);
        _query_result_scores.insert(i, score);
        
    } else if( i < _top_n_to_find ) {
        _query_results.push_back(node);
        _query_result_scores.push_back(score);
    }
    if( _query_result_scores.size() > _top_n_to_find ) {
        _query_result_scores.remove_at(_top_n_to_find);
        _query_results.remove_at(_top_n_to_find);
    }
}

/**
 * Symptoms of premature optimization...
void UtilityAINQSSearchSpaces::apply_criterion( UtilityAISearchCriteria* criteria, 
                                                TypedArray<Node> search_space, 
                                                TypedArray<double> current_scores, 
                                                TypedArray<Node>& result_space, 
                                                TypedArray<double>& result_scores ) {
    TypedArray<Node> new_space;
    TypedArray<double> new_scoring;
    for( int i = 0; i < search_space.size(); ++i ) {

    }

}
/**/

