#include "UtilityAIConsiderationGroup.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIConsiderationGroup::_bind_methods() {
   
    ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAIConsiderationGroup::set_evaluation_method);
    ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAIConsiderationGroup::get_evaluation_method);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5,OneMinusScore:6"), "set_evaluation_method","get_evaluation_method");
    
    /**
    ClassDB::bind_method(D_METHOD("change_to_state", "target_state_name"), &UtilityAIConsiderationGroup::_change_to_state);
    
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &UtilityAIConsiderationGroup::_update_current_state);
    /**/
}


// Constructor and destructor.

UtilityAIConsiderationGroup::UtilityAIConsiderationGroup() {
}


UtilityAIConsiderationGroup::~UtilityAIConsiderationGroup() {
}

// Handling functions.



// Getters and Setters.

void UtilityAIConsiderationGroup::set_evaluation_method( int evaluation_method ) {
    _evaluation_method = evaluation_method;
}

int UtilityAIConsiderationGroup::get_evaluation_method() const {
    return _evaluation_method;
}


// Godot virtuals.
/**
void UtilityAIConsiderationGroup::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIConsiderationGroup::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIConsiderationGroup error, no child nodes (states) have been added to the UtilityAIConsiderationGroup '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIConsiderationGroupState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIConsiderationGroup error, the first child is not a UtilityAIConsiderationGroupState node.");
    _current_state->_enter_state();
}

void UtilityAIConsiderationGroup::_process(double delta ) {
    //if( _update_method != UtilityAIConsiderationGroup_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIConsiderationGroup::_physics_process(double delta ) {
    //if( _update_method != UtilityAIConsiderationGroup_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/

double UtilityAIConsiderationGroup::evaluate() { //UtilityAIAgent* agent, double delta) {
    if( !get_is_active() ) return 0.0;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0;

    _score = 0.0;
    _has_vetoed = false;
    
    // Evaluate the children.
    int num_children = get_child_count();
    if( num_children < 1 ) return 0.0;
    double child_score = 0.0;
    double one_over_num_children = 1.0 / (double)num_children;
    for( int i = 0; i < num_children; ++i ) {
        UtilityAIConsiderations* considerationNode = godot::Object::cast_to<UtilityAIConsiderations>(get_child(i));
        if( considerationNode == nullptr ) continue;
        if( !considerationNode->get_is_active() ) continue;
        child_score = considerationNode->evaluate(); //agent, delta);
        if( considerationNode->get_has_vetoed()) {
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
            case UtilityAIConsiderationGroupEvaluationMethod::Mean: 
            {
                _score += (child_score * one_over_num_children);
            }
            break;
            case UtilityAIConsiderationGroupEvaluationMethod::Multiply: 
            {
                if( i == 0 ) _score = child_score;
                else _score *= child_score;
            }
            break;
            case UtilityAIConsiderationGroupEvaluationMethod::FirstNonZero: 
            {
                if( child_score > 0.0 ) {
                    _score = child_score;
                    return _score;
                }
            }
            break;
            default: _score += child_score;
        }//end switch evaluation method
        
    }//endfor children

    if( _evaluation_method == UtilityAIConsiderationGroupEvaluationMethod::OneMinusScore ) {
        _score = 1.0 - _score;
    }

    return _score;
}

