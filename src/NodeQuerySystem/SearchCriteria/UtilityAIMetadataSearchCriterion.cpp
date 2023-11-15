#include "UtilityAIMetadataSearchCriterion.h"

using namespace godot;



UtilityAIMetadataSearchCriterion::UtilityAIMetadataSearchCriterion() {

}

UtilityAIMetadataSearchCriterion::~UtilityAIMetadataSearchCriterion() {

}

// Getters and setters.

void UtilityAIMetadataSearchCriterion::set_metadata_name( StringName _metadata_name ) {
    _metadata_name = _metadata_name;
}


StringName UtilityAIMetadataSearchCriterion::get_metadata_name() const {
    return _metadata_name;
}

void UtilityAIMetadataSearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    _score = 1.0;
    godot::Variant metavar = node->get_meta(_metadata_name, "UAI*NAN");
    _is_filtered = (metavar != godot::Variant("UAI*NAN"));
    filter_out = _is_filtered;
    score = _score;
}