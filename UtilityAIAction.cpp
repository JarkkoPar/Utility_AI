#include "UtilityAIAction.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIAction::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_action_id", "action_id"), &UtilityAIAction::set_action_id);
    ClassDB::bind_method(D_METHOD("get_action_id"), &UtilityAIAction::get_action_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "action_id", PROPERTY_HINT_NONE), "set_action_id","get_action_id");
    

}


// Constructor and destructor.

UtilityAIAction::UtilityAIAction() {
    _action_id = 0;
}


UtilityAIAction::~UtilityAIAction() {
}

// Handling functions.


bool UtilityAIAction::start_action() {
    set_is_finished(false);
    return true;
}

bool UtilityAIAction::end_action() {
    set_is_finished(false);
    return true;
}

Node* UtilityAIAction::step_actions() {
    if( get_is_finished() ) {
        set_is_finished(false);
        return nullptr;
    }
    return this;
}


// Getters and Setters.

void UtilityAIAction::set_action_id( int action_id ) {
    _action_id = action_id;
}

int  UtilityAIAction::get_action_id() const {
    return _action_id;
}


/**
void UtilityAIAction::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool UtilityAIAction::get_is_active() const {
    return _is_active;
}

void UtilityAIAction::set_update_method( int update_method ) {
    _update_method = update_method;
}

int UtilityAIAction::get_update_method() const {
    return _update_method;
}
/**/

// Godot virtuals.
/**
void UtilityAIAction::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIAction::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIAction error, no child nodes (states) have been added to the UtilityAIAction '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIActionState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIAction error, the first child is not a UtilityAIActionState node.");
    _current_state->_enter_state();
}

void UtilityAIAction::_process(double delta ) {
    //if( _update_method != UtilityAIAction_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIAction::_physics_process(double delta ) {
    //if( _update_method != UtilityAIAction_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/
