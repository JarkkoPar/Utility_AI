#include "UtilityAIBehaviourTreeNodes.h"
#include "../UtilityAIConsiderations.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBehaviourTreeNodes::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAIBehaviourTreeNodes::set_evaluation_method);
    ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAIBehaviourTreeNodes::get_evaluation_method);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method","get_evaluation_method");

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviourTreeNodes::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviourTreeNodes::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");

}


// Constructor and destructor.

UtilityAIBehaviourTreeNodes::UtilityAIBehaviourTreeNodes() {
    _score = 0.0;
    _evaluation_method = UtilityAIBehaviourTreeNodesEvaluationMethod::Multiply;
    _invert_score = false;
}


UtilityAIBehaviourTreeNodes::~UtilityAIBehaviourTreeNodes() {
}


// Getters and Setters.


void UtilityAIBehaviourTreeNodes::set_evaluation_method( int evaluation_method ) {
    _evaluation_method = evaluation_method;
}

int UtilityAIBehaviourTreeNodes::get_evaluation_method() const {
    return _evaluation_method;
}

void UtilityAIBehaviourTreeNodes::set_score( double score ) {
    _score = score;
}


double UtilityAIBehaviourTreeNodes::get_score() const {
    return _score;
}


// Handling methods.

double UtilityAIBehaviourTreeNodes::evaluate() {
    if( !get_is_active() ) return 0.0;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0;

    _score = 0.0;
    
    // Evaluate the children.
    int num_children = get_child_count();
    if( num_children < 1 ) return 0.0;
    double child_score = 0.0;
    for( int i = 0; i < num_children; ++i ) {
        Node* node = get_child(i);
        if( node == nullptr ) continue;
        UtilityAIConsiderations* considerationNode = godot::Object::cast_to<UtilityAIConsiderations>(node);
        if( considerationNode == nullptr ) continue;
        if( !considerationNode->get_is_active() ) continue;
        child_score = considerationNode->evaluate();
        if( considerationNode->get_has_vetoed()) {
            _score = 0.0;
            return 0.0; // Veto zeroes out the score for the entire group.
        }

        switch( _evaluation_method ) {
            case UtilityAIBehaviourTreeNodesEvaluationMethod::Min: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score < _score ) _score = child_score;
            }
            break;
            case UtilityAIBehaviourTreeNodesEvaluationMethod::Max: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score > _score ) _score = child_score;
            }
            break;
            case UtilityAIBehaviourTreeNodesEvaluationMethod::Multiply: 
            {
                if( i == 0 ) _score = child_score;
                else _score *= child_score;
                // If after multiplication we are at 0.0, then none of the
                // other considerations will ever change the result, so bail.
                if( _score == 0.0 ) {
                    if( _invert_score ) {
                        _score = 1.0;
                        return 1.0;
                    }
                    _score = 0.0;
                    return 0.0;
                }
            }
            break;
            case UtilityAIBehaviourTreeNodesEvaluationMethod::FirstNonZero: 
            {
                if( child_score > 0.0 ) {
                    if( _invert_score ) {
                        _score = 1.0 - child_score;
                    } else {
                        _score = child_score;
                    }
                    return _score;
                }
            }
            break;
            default: _score += child_score;
        }//end switch evaluation method
        
    }//endfor children

    if( _evaluation_method == UtilityAIBehaviourTreeNodesEvaluationMethod::Mean ) {
        _score = _score / ((double)num_children);
    }

    if( _invert_score ) {
        _score = 1.0 - _score;
    }

    return _score;
}

int UtilityAIBehaviourTreeNodes::tick(Variant user_data, double delta) { 
    return 0;
}


