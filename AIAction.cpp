#include "AIAction.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void AIAction::_bind_methods() {
    /*ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &AIAction::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &AIAction::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
    
    //ClassDB::bind_method(D_METHOD("set_update_method", "update_method"), &AIAction::set_update_method);
    //ClassDB::bind_method(D_METHOD("get_update_method"), &AIAction::get_update_method);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "update_method", PROPERTY_HINT_ENUM, "Process:0,Physics process:1,Manual:2"), "set_update_method","get_update_method");
    

    ClassDB::bind_method(D_METHOD("change_to_state", "target_state_name"), &AIAction::_change_to_state);
    
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &AIAction::_update_current_state);
    /**/
}


// Constructor and destructor.

AIAction::AIAction() {
}


AIAction::~AIAction() {
}

// Handling functions.



// Getters and Setters.
/**
void AIAction::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool AIAction::get_is_active() const {
    return _is_active;
}

void AIAction::set_update_method( int update_method ) {
    _update_method = update_method;
}

int AIAction::get_update_method() const {
    return _update_method;
}
/**/

// Godot virtuals.
/**
void AIAction::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void AIAction::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "AIAction error, no child nodes (states) have been added to the AIAction '" + get_name() + "'.");
    _current_state = Object::cast_to<AIActionState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "AIAction error, the first child is not a AIActionState node.");
    _current_state->_enter_state();
}

void AIAction::_process(double delta ) {
    //if( _update_method != AIAction_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void AIAction::_physics_process(double delta ) {
    //if( _update_method != AIAction_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/
