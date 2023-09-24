#include "AIConsideration.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void AIConsideration::_bind_methods() {
    /*ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &AIConsideration::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &AIConsideration::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
    
    //ClassDB::bind_method(D_METHOD("set_update_method", "update_method"), &AIConsideration::set_update_method);
    //ClassDB::bind_method(D_METHOD("get_update_method"), &AIConsideration::get_update_method);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "update_method", PROPERTY_HINT_ENUM, "Process:0,Physics process:1,Manual:2"), "set_update_method","get_update_method");
    

    ClassDB::bind_method(D_METHOD("change_to_state", "target_state_name"), &AIConsideration::_change_to_state);
    
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &AIConsideration::_update_current_state);
    /**/
}


// Constructor and destructor.

AIConsideration::AIConsideration() {
}


AIConsideration::~AIConsideration() {
}

// Handling functions.



// Getters and Setters.
/**
void AIConsideration::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool AIConsideration::get_is_active() const {
    return _is_active;
}

void AIConsideration::set_update_method( int update_method ) {
    _update_method = update_method;
}

int AIConsideration::get_update_method() const {
    return _update_method;
}
/**/

// Godot virtuals.
/**
void AIConsideration::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void AIConsideration::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "AIConsideration error, no child nodes (states) have been added to the AIConsideration '" + get_name() + "'.");
    _current_state = Object::cast_to<AIConsiderationState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "AIConsideration error, the first child is not a AIConsiderationState node.");
    _current_state->_enter_state();
}

void AIConsideration::_process(double delta ) {
    //if( _update_method != AIConsideration_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void AIConsideration::_physics_process(double delta ) {
    //if( _update_method != AIConsideration_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/



float AIConsideration::evaluate() {
    if( !_is_active ) return 0.0f;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0f;

    _score = 0.0f;

    return _score;
}


