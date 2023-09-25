#include "UtilityAIConsiderations.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIConsiderations::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_has_vetoed", "has_vetoed"), &UtilityAIConsiderations::set_has_vetoed);
    ClassDB::bind_method(D_METHOD("get_has_vetoed"), &UtilityAIConsiderations::get_has_vetoed);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_vetoed", PROPERTY_HINT_NONE), "set_has_vetoed","get_has_vetoed");
    

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIConsiderations::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIConsiderations::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    

}


// Constructor and destructor.

UtilityAIConsiderations::UtilityAIConsiderations() {
    _has_vetoed = false;
    _score = 0.0f;
}


UtilityAIConsiderations::~UtilityAIConsiderations() {
}

// Handling functions.



// Getters and Setters.

void UtilityAIConsiderations::set_has_vetoed( bool has_vetoed ) {
    _has_vetoed = has_vetoed;
}

bool UtilityAIConsiderations::get_has_vetoed() const {
    return _has_vetoed;
}


void UtilityAIConsiderations::set_score( double score ) {
    _score = score;
}

double UtilityAIConsiderations::get_score() const {
    return _score;
}


// Godot virtuals.
/**
void UtilityAIConsiderations::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIConsiderations::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIConsiderations error, no child nodes (states) have been added to the UtilityAIConsiderations '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIConsiderationsState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIConsiderations error, the first child is not a UtilityAIConsiderationsState node.");
    _current_state->_enter_state();
}

void UtilityAIConsiderations::_process(double delta ) {
    //if( _update_method != UtilityAIConsiderations_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIConsiderations::_physics_process(double delta ) {
    //if( _update_method != UtilityAIConsiderations_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/


double UtilityAIConsiderations::evaluate(UtilityAIAgent* agent, double delta) {
    return 0.0;
}


