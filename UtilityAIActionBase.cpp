#include "UtilityAIActionBase.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIActionBase::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &UtilityAIActionBase::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &UtilityAIActionBase::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
    
    
}


// Constructor and destructor.

UtilityAIActionBase::UtilityAIActionBase() {
}


UtilityAIActionBase::~UtilityAIActionBase() {
}

// Handling functions.



// Getters and Setters.

void UtilityAIActionBase::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool UtilityAIActionBase::get_is_active() const {
    return _is_active;
}


// Godot virtuals.
/**
void UtilityAIActionBase::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIActionBase::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIActionBase error, no child nodes (states) have been added to the UtilityAIActionBase '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIActionBaseState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIActionBase error, the first child is not a UtilityAIActionBaseState node.");
    _current_state->_enter_state();
}

void UtilityAIActionBase::_process(double delta ) {
    //if( _update_method != UtilityAIActionBase_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIActionBase::_physics_process(double delta ) {
    //if( _update_method != UtilityAIActionBase_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/
