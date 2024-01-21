#include "custom.h"

using namespace godot;



UtilityAICustomSearchCriterion::UtilityAICustomSearchCriterion() {

}

UtilityAICustomSearchCriterion::~UtilityAICustomSearchCriterion() {

}

void UtilityAICustomSearchCriterion::apply_criterion( Node* node, bool& filter_out, float& score ) {
    if( !has_method("apply_criterion")) return;
    _score = 1.0f;
    _is_filtered = false;
    call("apply_criterion", node);
    filter_out = _is_filtered;
    score = _score;
}