#include "AIConsiderationGroup.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void AIConsiderationGroup::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &AIConsiderationGroup::set_is_active);
    //ClassDB::bind_method(D_METHOD("get_is_active"), &AIConsiderationGroup::get_is_active);
    //ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
    
    ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &AIConsiderationGroup::set_evaluation_method);
    ClassDB::bind_method(D_METHOD("get_evaluation_method"), &AIConsiderationGroup::get_evaluation_method);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method","get_evaluation_method");
    
    /**
    ClassDB::bind_method(D_METHOD("change_to_state", "target_state_name"), &AIConsiderationGroup::_change_to_state);
    
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &AIConsiderationGroup::_update_current_state);
    /**/
}


// Constructor and destructor.

AIConsiderationGroup::AIConsiderationGroup() {
}


AIConsiderationGroup::~AIConsiderationGroup() {
}

// Handling functions.



// Getters and Setters.

void AIConsiderationGroup::set_evaluation_method( int evaluation_method ) {
    _evaluation_method = evaluation_method;
}

int AIConsiderationGroup::get_evaluation_method() const {
    return _evaluation_method;
}


// Godot virtuals.
/**
void AIConsiderationGroup::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void AIConsiderationGroup::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "AIConsiderationGroup error, no child nodes (states) have been added to the AIConsiderationGroup '" + get_name() + "'.");
    _current_state = Object::cast_to<AIConsiderationGroupState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "AIConsiderationGroup error, the first child is not a AIConsiderationGroupState node.");
    _current_state->_enter_state();
}

void AIConsiderationGroup::_process(double delta ) {
    //if( _update_method != AIConsiderationGroup_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void AIConsiderationGroup::_physics_process(double delta ) {
    //if( _update_method != AIConsiderationGroup_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/

float AIConsiderationGroup::evaluate() {
    if( !_is_active ) return 0.0f;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0f;

    _score = 0.0f;
    
    // Evaluate the children.
    int num_children = get_child_count();
    if( num_children < 1 ) return 0.0f;
    float child_score = 0.0f;
    float one_over_num_children = 1.0f / (float)num_children;
    for( int i = 0; i < num_children; ++i ) {
        AIConsiderationBase* considerationNode = godot::Object::cast_to<AIConsiderationBase>(get_child(i));
        if( considerationNode == nullptr ) continue;
        
        child_score = considerationNode->evaluate();
        if( considerationNode->get_has_vetoed()) {
            _score = 0.0f;
            return _score; // Veto zeroes out the score.
        }

        switch( _evaluation_method ) {
            case AIConsiderationGroupEvaluationMethod::Min: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score < _score ) _score = child_score;
            }
            break;
            case AIConsiderationGroupEvaluationMethod::Max: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score > _score ) _score = child_score;
            }
            break;
            case AIConsiderationGroupEvaluationMethod::Mean: 
            {
                _score += (child_score * one_over_num_children);
            }
            break;
            case AIConsiderationGroupEvaluationMethod::Multiply: 
            {
                if( i == 0 ) _score = child_score;
                else _score *= child_score;
            }
            break;
            case AIConsiderationGroupEvaluationMethod::FirstNonZero: 
            {
                if( child_score > 0.0f ) {
                    _score = child_score;
                    return _score;
                }
            }
            break;
            default: _score += child_score;
        }
        
    }//endfor children

    return _score;
}

