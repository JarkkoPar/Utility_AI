#include "UtilityAIActions.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIActions::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_finished", "is_finished"), &UtilityAIActions::set_is_finished);
    ClassDB::bind_method(D_METHOD("get_is_finished"), &UtilityAIActions::get_is_finished);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_finished", PROPERTY_HINT_NONE), "set_is_finished","get_is_finished");
    
}


// Constructor and destructor.

UtilityAIActions::UtilityAIActions() {
    _is_finished = false;
}


UtilityAIActions::~UtilityAIActions() {

}

// Handling functions.

bool UtilityAIActions::start_action() {
    _is_finished = false;
    return true;
}

bool UtilityAIActions::end_action() {
    _is_finished = false;
    return true;
}

Node* UtilityAIActions::step_actions() {


    return nullptr;
}


// Getters and Setters.

void UtilityAIActions::set_is_finished( bool is_finished ) {
    _is_finished = is_finished;
}

bool UtilityAIActions::get_is_finished() const {
    return _is_finished;
}



// Godot virtuals.
/**
void UtilityAIActions::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIActions::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIActions error, no child nodes (states) have been added to the UtilityAIActions '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIActionsState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIActions error, the first child is not a UtilityAIActionsState node.");
    _current_state->_enter_state();
}

void UtilityAIActions::_process(double delta ) {
    //if( _update_method != UtilityAIActions_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIActions::_physics_process(double delta ) {
    //if( _update_method != UtilityAIActions_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/
