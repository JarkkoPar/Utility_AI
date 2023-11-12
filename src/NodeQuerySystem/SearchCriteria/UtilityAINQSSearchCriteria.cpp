#include "UtilityAINQSSearchCriteria.h"


using namespace godot;


UtilityAINQSSearchCriteria::UtilityAINQSSearchCriteria() {
    _is_filtered = true;
    _is_scored = true;

    _filtering_result = false;
    _scoring_result = 0.0;
}


UtilityAINQSSearchCriteria::~UtilityAINQSSearchCriteria() {

}


void UtilityAINQSSearchCriteria::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_filtered", "is_filtered"), &UtilityAINQSSearchCriteria::set_is_filtered);
    ClassDB::bind_method(D_METHOD("get_is_filtered"), &UtilityAINQSSearchCriteria::get_is_filtered);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_filtered", PROPERTY_HINT_NONE), "set_is_filtered","get_is_filtered");
    
    ClassDB::bind_method(D_METHOD("set_is_scored", "is_scored"), &UtilityAINQSSearchCriteria::set_is_scored);
    ClassDB::bind_method(D_METHOD("get_is_scored"), &UtilityAINQSSearchCriteria::get_is_scored);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_scored", PROPERTY_HINT_NONE), "set_is_scored","get_is_scored");
    
    ClassDB::bind_method(D_METHOD("set_filtering_result", "filtering_result"), &UtilityAINQSSearchCriteria::set_filtering_result);
    ClassDB::bind_method(D_METHOD("get_filtering_result"), &UtilityAINQSSearchCriteria::get_filtering_result);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "filtering_result", PROPERTY_HINT_NONE), "set_filtering_result","get_filtering_result");
    
    ClassDB::bind_method(D_METHOD("set_scoring_result", "scoring_result"), &UtilityAINQSSearchCriteria::set_scoring_result);
    ClassDB::bind_method(D_METHOD("get_scoring_result"), &UtilityAINQSSearchCriteria::get_scoring_result);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "scoring_result", PROPERTY_HINT_NONE), "set_scoring_result","get_scoring_result");
    
}

    
// Getters and setters.
    
void UtilityAINQSSearchCriteria::set_is_filtered( bool is_filtered ) {
    _is_filtered = is_filtered;
}


bool UtilityAINQSSearchCriteria::get_is_filtered() const {
    return _is_filtered;
}


void UtilityAINQSSearchCriteria::set_is_scored( bool is_scored ) {
    _is_scored = is_scored;
}


bool UtilityAINQSSearchCriteria::get_is_scored() const {
    return _is_scored;
}


void UtilityAINQSSearchCriteria::set_filtering_result( bool filtering_result ) {
    _filtering_result = filtering_result;
}


bool UtilityAINQSSearchCriteria::get_filtering_result() const {
    return _filtering_result;
}


void UtilityAINQSSearchCriteria::set_scoring_result( double scoring_result ) {
    _scoring_result = scoring_result;
}


double UtilityAINQSSearchCriteria::get_scoring_result() const {
    return _scoring_result;
}


// Handing methods.

void UtilityAINQSSearchCriteria::apply_criterion( Node* node, bool& filter_out, double& score ) {
    if( node == nullptr ) return;


}