#include "UtilityAINQSSearchCriteria.h"


using namespace godot;


UtilityAINQSSearchCriteria::UtilityAINQSSearchCriteria() {
    _is_filtered = true;
    _use_for_scoring = true;

    _use_for_filtering = false;
    _score = 0.0;
}


UtilityAINQSSearchCriteria::~UtilityAINQSSearchCriteria() {

}


void UtilityAINQSSearchCriteria::_ready() {
    _initialize_criterion();
}



void UtilityAINQSSearchCriteria::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_use_for_scoring", "use_for_scoring"), &UtilityAINQSSearchCriteria::set_use_for_scoring);
    ClassDB::bind_method(D_METHOD("get_use_for_scoring"), &UtilityAINQSSearchCriteria::get_use_for_scoring);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_for_scoring", PROPERTY_HINT_NONE), "set_use_for_scoring","get_use_for_scoring");
    
    ClassDB::bind_method(D_METHOD("set_use_for_filtering", "use_for_filtering"), &UtilityAINQSSearchCriteria::set_use_for_filtering);
    ClassDB::bind_method(D_METHOD("get_use_for_filtering"), &UtilityAINQSSearchCriteria::get_use_for_filtering);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_for_filtering", PROPERTY_HINT_NONE), "set_use_for_filtering","get_use_for_filtering");
    
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAINQSSearchCriteria::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAINQSSearchCriteria::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE), "set_score","get_score");
    
    ClassDB::bind_method(D_METHOD("set_is_filtered", "is_filtered"), &UtilityAINQSSearchCriteria::set_is_filtered);
    ClassDB::bind_method(D_METHOD("get_is_filtered"), &UtilityAINQSSearchCriteria::get_is_filtered);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_filtered", PROPERTY_HINT_NONE), "set_is_filtered","get_is_filtered");
    
}

    
// Getters and setters.
    
void UtilityAINQSSearchCriteria::set_is_filtered( bool is_filtered ) {
    _is_filtered = is_filtered;
}


bool UtilityAINQSSearchCriteria::get_is_filtered() const {
    return _is_filtered;
}


void UtilityAINQSSearchCriteria::set_use_for_scoring( bool use_for_scoring ) {
    _use_for_scoring = use_for_scoring;
}


bool UtilityAINQSSearchCriteria::get_use_for_scoring() const {
    return _use_for_scoring;
}


void UtilityAINQSSearchCriteria::set_use_for_filtering( bool use_for_filtering ) {
    _use_for_filtering = use_for_filtering;
}


bool UtilityAINQSSearchCriteria::get_use_for_filtering() const {
    return _use_for_filtering;
}


void UtilityAINQSSearchCriteria::set_score( double score ) {
    _score = score;
}


double UtilityAINQSSearchCriteria::get_score() const {
    return _score;
}


// Handing methods.

void UtilityAINQSSearchCriteria::apply_criterion( Node* node, bool& filter_out, double& score ) {
    if( node == nullptr ) return;


}