#include "UtilityAIActionGroup.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIActionGroup::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_action_execution_rule", "action_execution_rule"), &UtilityAIActionGroup::set_action_execution_rule);
    ClassDB::bind_method(D_METHOD("get_action_execution_rule"), &UtilityAIActionGroup::get_action_execution_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "action_execution_rule", PROPERTY_HINT_ENUM, "Sequence:0,PickOneAtRandom:1"), "set_action_execution_rule","get_action_execution_rule");
    
    ClassDB::bind_method(D_METHOD("set_current_action_index", "current_action_index"), &UtilityAIActionGroup::set_current_action_index);
    ClassDB::bind_method(D_METHOD("get_current_action_index"), &UtilityAIActionGroup::get_current_action_index);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_action_index", PROPERTY_HINT_RANGE,"-0,256"), "set_current_action_index","get_current_action_index");
    
}


// Constructor and destructor.

UtilityAIActionGroup::UtilityAIActionGroup() {
    _action_execution_rule = UtilityAIActionGroupExecutionRule::Sequence;
    //_action_execution_index = 0;
    _current_action_index = 0;
}


UtilityAIActionGroup::~UtilityAIActionGroup() {
}

// Handling functions.

bool UtilityAIActionGroup::start_action() {
    if( get_child_count() <= 0 ) return false;
    //_action_execution_index = 0;
    _current_action_index = 0;
    return true;
}

// Getters and Setters.

void UtilityAIActionGroup::set_action_execution_rule( int action_execution_rule ) {
    _action_execution_rule = action_execution_rule;
}

int UtilityAIActionGroup::get_action_execution_rule() const {
    return _action_execution_rule;
}

void UtilityAIActionGroup::set_current_action_index( int current_action_index ) {
    _current_action_index = current_action_index;
}

int  UtilityAIActionGroup::get_current_action_index() const {
    return _current_action_index;
}

/**/

// Godot virtuals.
/**
void UtilityAIActionGroup::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIActionGroup::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIActionGroup error, no child nodes (states) have been added to the UtilityAIActionGroup '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIActionGroupState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIActionGroup error, the first child is not a UtilityAIActionGroupState node.");
    _current_state->_enter_state();
}

void UtilityAIActionGroup::_process(double delta ) {
    //if( _update_method != UtilityAIActionGroup_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_actions(delta);
}

void UtilityAIActionGroup::_physics_process(double delta ) {
    //if( _update_method != UtilityAIActionGroup_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_actions(delta);
}

/**/
