#include "UtilityAIConsideration.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIConsideration::_bind_methods() {
    /*ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &UtilityAIConsideration::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &UtilityAIConsideration::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
    
    //ClassDB::bind_method(D_METHOD("set_update_method", "update_method"), &UtilityAIConsideration::set_update_method);
    //ClassDB::bind_method(D_METHOD("get_update_method"), &UtilityAIConsideration::get_update_method);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "update_method", PROPERTY_HINT_ENUM, "Process:0,Physics process:1,Manual:2"), "set_update_method","get_update_method");
    

    ClassDB::bind_method(D_METHOD("change_to_state", "target_state_name"), &UtilityAIConsideration::_change_to_state);
    
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &UtilityAIConsideration::_update_current_state);
    /**/
}


// Constructor and destructor.

UtilityAIConsideration::UtilityAIConsideration() {
}


UtilityAIConsideration::~UtilityAIConsideration() {
}

// Handling functions.



// Getters and Setters.
/**
void UtilityAIConsideration::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool UtilityAIConsideration::get_is_active() const {
    return _is_active;
}

void UtilityAIConsideration::set_update_method( int update_method ) {
    _update_method = update_method;
}

int UtilityAIConsideration::get_update_method() const {
    return _update_method;
}
/**/

// Godot virtuals.
/**
void UtilityAIConsideration::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIConsideration::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIConsideration error, no child nodes (states) have been added to the UtilityAIConsideration '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIConsiderationState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIConsideration error, the first child is not a UtilityAIConsiderationState node.");
    _current_state->_enter_state();
}

void UtilityAIConsideration::_process(double delta ) {
    //if( _update_method != UtilityAIConsideration_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIConsideration::_physics_process(double delta ) {
    //if( _update_method != UtilityAIConsideration_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/



float UtilityAIConsideration::evaluate() {
    if( !_is_active ) return 0.0f;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0f;

    _score = 0.0f;

    return _score;
}


