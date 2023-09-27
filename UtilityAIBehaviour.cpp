#include "UtilityAIBehaviour.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

#include "UtilityAIConsideration.h"
#include "UtilityAIConsiderationGroup.h"


using namespace godot;

// Method binds.

void UtilityAIBehaviour::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviour::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviour::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_RANGE,"-100.0,100.0"), "set_score","get_score");
    
    ClassDB::bind_method(D_METHOD("set_cooldown_seconds", "cooldown_seconds"), &UtilityAIBehaviour::set_cooldown_seconds);
    ClassDB::bind_method(D_METHOD("get_cooldown_seconds"), &UtilityAIBehaviour::get_cooldown_seconds);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "cooldown_seconds", PROPERTY_HINT_RANGE, "0.0,600.0,allow_greater"), "set_cooldown_seconds","get_cooldown_seconds");
    
    ClassDB::bind_method(D_METHOD("set_current_action_index", "current_action_index"), &UtilityAIBehaviour::set_current_action_index);
    ClassDB::bind_method(D_METHOD("get_current_action_index"), &UtilityAIBehaviour::get_current_action_index);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_action_index", PROPERTY_HINT_RANGE,"-0,256"), "set_current_action_index","get_current_action_index");
    
    
    //ClassDB::bind_method(D_METHOD("evaluate"), &UtilityAIBehaviour::evaluate);
    /**
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &UtilityAIBehaviour::_update_current_state);
    /**/
}


// Constructor and destructor.

UtilityAIBehaviour::UtilityAIBehaviour() {
    _score = 0.0f;
    _cooldown_seconds = 0.0;
    _current_cooldown_seconds = 0.0;
    _current_action_index = 0;
}


UtilityAIBehaviour::~UtilityAIBehaviour() {
}

// Handling functions.




// Getters and Setters.

void UtilityAIBehaviour::set_score( float score ) {
    _score = score;
}

float UtilityAIBehaviour::get_score() const {
    return _score;
}

void UtilityAIBehaviour::set_cooldown_seconds( double cooldown_seconds ) {
    _cooldown_seconds = cooldown_seconds;
}

double UtilityAIBehaviour::get_cooldown_seconds() const {
    return _cooldown_seconds;
}

void UtilityAIBehaviour::set_current_action_index( int current_action_index ) {
    _current_action_index = current_action_index;
}

int  UtilityAIBehaviour::get_current_action_index() const {
    return _current_action_index;
}


/**
void UtilityAIBehaviour::set_update_method( int update_method ) {
    _update_method = update_method;
}

int UtilityAIBehaviour::get_update_method() const {
    return _update_method;
}
/**/

// Godot virtuals.

void UtilityAIBehaviour::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIBehaviour::_ready() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    // Get the considerations and actions.    
    
}

/*void UtilityAIBehaviour::_process(double delta ) {
    //if( _update_method != UtilityAIBehaviour_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_Behaviours(delta);
}

void UtilityAIBehaviour::_physics_process(double delta ) {
    //if( _update_method != UtilityAIBehaviour_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_Behaviours(delta);
}

/**/


// Handling functions.

double UtilityAIBehaviour::evaluate() { // UtilityAIAgent* agent, double delta) {
    if( !get_is_active() ) return 0.0;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0;

    // If the behaviour is on cooldown, it cannot be chosen.
    //if( _current_cooldown_seconds > 0.0 ) {
    //    _current_cooldown_seconds -= delta;
    //    return 0.0;
    //}

    _score = 0.0;

    // Evaluate the children.
    int num_children = get_child_count();
    for( int i = 0; i < num_children; ++i ) {
        UtilityAIConsiderations* considerationNode = godot::Object::cast_to<UtilityAIConsiderations>(get_child(i));
        if( considerationNode == nullptr ) continue;
        if( !considerationNode->get_is_active() ) continue;
        _score += considerationNode->evaluate();//agent, delta);
        if( considerationNode->get_has_vetoed()){
            _score = 0.0;
            return 0.0; // The consideration vetoed this behaviour.
        }
    }//endfor children

    return _score;
}


void UtilityAIBehaviour::start_behaviour() {
    _current_cooldown_seconds = _cooldown_seconds;
    _current_action_index = 0;
}


void UtilityAIBehaviour::end_behaviour() {
    
}
