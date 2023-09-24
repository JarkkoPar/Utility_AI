#include "UtilityAIConsiderationBase.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIConsiderationBase::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &UtilityAIConsiderationBase::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &UtilityAIConsiderationBase::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
    
    ClassDB::bind_method(D_METHOD("set_has_vetoed", "has_vetoed"), &UtilityAIConsiderationBase::set_has_vetoed);
    ClassDB::bind_method(D_METHOD("get_has_vetoed"), &UtilityAIConsiderationBase::get_has_vetoed);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_vetoed", PROPERTY_HINT_NONE), "set_has_vetoed","get_has_vetoed");
    

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIConsiderationBase::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIConsiderationBase::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    

}


// Constructor and destructor.

UtilityAIConsiderationBase::UtilityAIConsiderationBase() {
    _is_active = true;
    _has_vetoed = false;
    _score = 0.0f;
}


UtilityAIConsiderationBase::~UtilityAIConsiderationBase() {
}

// Handling functions.



// Getters and Setters.

void UtilityAIConsiderationBase::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool UtilityAIConsiderationBase::get_is_active() const {
    return _is_active;
}

void UtilityAIConsiderationBase::set_has_vetoed( bool has_vetoed ) {
    _has_vetoed = has_vetoed;
}

bool UtilityAIConsiderationBase::get_has_vetoed() const {
    return _has_vetoed;
}


void UtilityAIConsiderationBase::set_score( float score ) {
    _score = score;
}

float UtilityAIConsiderationBase::get_score() const {
    return _score;
}

/**
void UtilityAIConsiderationBase::set_update_method( int update_method ) {
    _update_method = update_method;
}

int UtilityAIConsiderationBase::get_update_method() const {
    return _update_method;
}
/**/

// Godot virtuals.
/**
void UtilityAIConsiderationBase::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIConsiderationBase::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIConsiderationBase error, no child nodes (states) have been added to the UtilityAIConsiderationBase '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIConsiderationBaseState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIConsiderationBase error, the first child is not a UtilityAIConsiderationBaseState node.");
    _current_state->_enter_state();
}

void UtilityAIConsiderationBase::_process(double delta ) {
    //if( _update_method != UtilityAIConsiderationBase_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIConsiderationBase::_physics_process(double delta ) {
    //if( _update_method != UtilityAIConsiderationBase_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/


float UtilityAIConsiderationBase::evaluate() {
    return 0.0f;
}


