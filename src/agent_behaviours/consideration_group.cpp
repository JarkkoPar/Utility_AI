#include "consideration_group.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIConsiderationGroup::_bind_methods() {
   
    ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAIConsiderationGroup::set_evaluation_method);
    ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAIConsiderationGroup::get_evaluation_method);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method","get_evaluation_method");

    ClassDB::bind_method(D_METHOD("set_invert_score", "invert_score"), &UtilityAIConsiderationGroup::set_invert_score);
    ClassDB::bind_method(D_METHOD("get_invert_score"), &UtilityAIConsiderationGroup::get_invert_score);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "invert_score", PROPERTY_HINT_NONE), "set_invert_score","get_invert_score");

}


// Constructor and destructor.

UtilityAIConsiderationGroup::UtilityAIConsiderationGroup() {
    _evaluation_method = 4; // Default to multiplication.
    _invert_score = false;
}


UtilityAIConsiderationGroup::~UtilityAIConsiderationGroup() {
}


// Getters and Setters.

void UtilityAIConsiderationGroup::set_evaluation_method( int evaluation_method ) {
    _evaluation_method = evaluation_method;
}

int UtilityAIConsiderationGroup::get_evaluation_method() const {
    return _evaluation_method;
}

void UtilityAIConsiderationGroup::set_invert_score( bool invert_score ) {
    _invert_score = invert_score;
}

bool UtilityAIConsiderationGroup::get_invert_score() const {
    return _invert_score;
}

// Handling functions.

float UtilityAIConsiderationGroup::evaluate() { 
    //if( !get_is_active() ) return 0.0;
    //if( Engine::get_singleton()->is_editor_hint() ) return 0.0;

    _score = 0.0;
    _has_vetoed = false;
    
    // Evaluate the children.
    int num_children = get_child_count();
    if( num_children < 1 ) return 0.0f;
    float child_score = 0.0f;
    for( int i = 0; i < num_children; ++i ) {
        Node* node = get_child(i);
        if( node == nullptr ) continue;
        UtilityAIConsiderations* considerationNode = godot::Object::cast_to<UtilityAIConsiderations>(node);
        if( considerationNode == nullptr ) continue;
        if( !considerationNode->get_is_active() ) continue;
        child_score = considerationNode->evaluate(); //agent, delta);
        if( considerationNode->get_has_vetoed() ) {
            _score = 0.0;
            _has_vetoed = true;
            return _score; // Veto zeroes out the score for the entire group.
        }

        switch( _evaluation_method ) {
            case UtilityAIConsiderationGroupEvaluationMethod::Min: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score < _score ) _score = child_score;
            }
            break;
            case UtilityAIConsiderationGroupEvaluationMethod::Max: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score > _score ) _score = child_score;
            }
            break;
            case UtilityAIConsiderationGroupEvaluationMethod::Multiply: 
            {
                if( i == 0 ) _score = child_score;
                else _score *= child_score;
                // If after multiplication we are at 0.0, then none of the
                // other considerations will ever change the result, so bail.
                if( _score == 0.0 ) {
                    if( _invert_score ) {
                        return 1.0;
                    }
                    return 0.0;
                }
            }
            break;
            case UtilityAIConsiderationGroupEvaluationMethod::FirstNonZero: 
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

    if( _evaluation_method == UtilityAIConsiderationGroupEvaluationMethod::Mean ) {
        _score = _score / ((float)num_children);
    }

    if( _invert_score ) {
        _score = 1.0 - _score;
    }

    return _score;
}

