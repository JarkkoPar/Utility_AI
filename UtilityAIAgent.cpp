#include "UtilityAIAgent.h"
#include "UtilityAIBehaviour.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIAgent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &UtilityAIAgent::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &UtilityAIAgent::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
    
    //ClassDB::bind_method(D_METHOD("set_update_method", "update_method"), &UtilityAIAgent::set_update_method);
    //ClassDB::bind_method(D_METHOD("get_update_method"), &UtilityAIAgent::get_update_method);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "update_method", PROPERTY_HINT_ENUM, "Process:0,Physics process:1,Manual:2"), "set_update_method","get_update_method");
    

    ClassDB::bind_method(D_METHOD("evaluate_options"), &UtilityAIAgent::evaluate_options);
    
    //ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &UtilityAIAgent::_update_current_state);
    /**/

    // Add all signals.

    ADD_SIGNAL(MethodInfo("behaviour_changed", PropertyInfo(Variant::OBJECT, "behaviour_node")));
}


// Constructor and destructor.

UtilityAIAgent::UtilityAIAgent() {
    _is_active = true;
    _chosen_behaviour_node = nullptr;
}


UtilityAIAgent::~UtilityAIAgent() {
}

// Handling functions.

void UtilityAIAgent::evaluate_options() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    // Go through the behaviours and check which one seems
    // best to perform.
    int chosen_node_index = 0;
    float highest_score = -1.0f;
    _chosen_behaviour_node = nullptr;
    
    // Evaluate the children.
    int num_children = get_child_count();
    if( num_children < 1 ) return; // Cannot evaluate without children.
    for( int i = 0; i < num_children; ++i ) {
        UtilityAIBehaviour* behaviourNode = godot::Object::cast_to<UtilityAIBehaviour>(get_child(i));
        if( behaviourNode == nullptr ) continue;

        float score = behaviourNode->evaluate();
        if( score > highest_score ) {
            highest_score = score;
            chosen_node_index = i;
            _chosen_behaviour_node = (Node*)behaviourNode;
        }
    }//endfor children

    // If no behaviour was chosen, use the default behaviour node.
    if( _chosen_behaviour_node == nullptr ) {
        // todo: code 
    } else {
        // Signal the chosen behaviour node.
        emit_signal("behaviour_changed", _chosen_behaviour_node);
    }
}

// Getters and Setters.

void UtilityAIAgent::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool UtilityAIAgent::get_is_active() const {
    return _is_active;
}



// Godot virtuals.
/**
void UtilityAIAgent::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIAgent::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    
    // Get the first state as the first child node and enter it.
    ERR_FAIL_COND_MSG( get_child_count() < 1, "UtilityAIAgent error, no child nodes (states) have been added to the UtilityAIAgent '" + get_name() + "'.");
    _current_state = Object::cast_to<UtilityAIAgentState>(get_child(0));
    ERR_FAIL_COND_MSG( _current_state == nullptr, "UtilityAIAgent error, the first child is not a UtilityAIAgentState node.");
    _current_state->_enter_state();
}

void UtilityAIAgent::_process(double delta ) {
    //if( _update_method != UtilityAIAgent_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_UtilityAIAgents(delta);
}

void UtilityAIAgent::_physics_process(double delta ) {
    //if( _update_method != UtilityAIAgent_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_UtilityAIAgents(delta);
}

/**/
