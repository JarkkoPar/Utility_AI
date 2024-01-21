#include "custom.h"

using namespace godot;



UtilityAICustomSearchCriterion::UtilityAICustomSearchCriterion() {

}

UtilityAICustomSearchCriterion::~UtilityAICustomSearchCriterion() {

}

void UtilityAICustomSearchCriterion::apply_criterion( Node* node, bool& filter_out, float& score ) {
    _score = 1.0f;
    _is_filtered = false;
    if( !has_method("apply_criterion")) return;
    call("apply_criterion", node);
    filter_out = _is_filtered;
    score = _score;
}