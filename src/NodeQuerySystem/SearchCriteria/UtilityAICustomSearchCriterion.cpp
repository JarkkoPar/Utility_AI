#include "UtilityAICustomSearchCriterion.h"

using namespace godot;



UtilityAICustomSearchCriterion::UtilityAICustomSearchCriterion() {

}

UtilityAICustomSearchCriterion::~UtilityAICustomSearchCriterion() {

}

void UtilityAICustomSearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    if( !has_method("apply_criterion")) return;
    call("apply_criterion", node);
    filter_out = _is_filtered;
    score = _score;
}