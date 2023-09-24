#include "AIBehaviour.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

#include "AIConsideration.h"
#include "AIConsiderationGroup.h"


using namespace godot;

// Method binds.

void AIBehaviour::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_is_active", "is_active"), &AIBehaviour::set_is_active);
    ClassDB::bind_method(D_METHOD("get_is_active"), &AIBehaviour::get_is_active);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active", PROPERTY_HINT_NONE), "set_is_active","get_is_active");
    
    ClassDB::bind_method(D_METHOD("set_score", "score"), &AIBehaviour::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &AIBehaviour::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_RANGE,"-100.0,100.0"), "set_score","get_score");
    
    //ClassDB::bind_method(D_METHOD("set_update_method", "update_method"), &AIBehaviour::set_update_method);
    //ClassDB::bind_method(D_METHOD("get_update_method"), &AIBehaviour::get_update_method);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "update_method", PROPERTY_HINT_ENUM, "Process:0,Physics process:1,Manual:2"), "set_update_method","get_update_method");
    
    
    ClassDB::bind_method(D_METHOD("evaluate"), &AIBehaviour::evaluate);
    /**
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &AIBehaviour::_update_current_state);
    /**/
}


// Constructor and destructor.

AIBehaviour::AIBehaviour() {
    _is_active = true;
    _score = 0.0f;
}


AIBehaviour::~AIBehaviour() {
}

// Handling functions.



// Getters and Setters.

void AIBehaviour::set_is_active( bool is_active ) {
    _is_active = is_active;
}

bool AIBehaviour::get_is_active() const {
    return _is_active;
}

void AIBehaviour::set_score( float score ) {
    _score = score;
}

float AIBehaviour::get_score() const {
    return _score;
}

/**
void AIBehaviour::set_update_method( int update_method ) {
    _update_method = update_method;
}

int AIBehaviour::get_update_method() const {
    return _update_method;
}
/**/

// Godot virtuals.

void AIBehaviour::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void AIBehaviour::_ready() {
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    // Get the considerations and actions.    
    
}

/*void AIBehaviour::_process(double delta ) {
    //if( _update_method != AIBehaviour_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_Behaviours(delta);
}

void AIBehaviour::_physics_process(double delta ) {
    //if( _update_method != AIBehaviour_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_Behaviours(delta);
}

/**/


// Handling functions.

float AIBehaviour::evaluate() {
    if( !_is_active ) return 0.0f;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0f;

    _score = 0.0f;

    // Evaluate the children.
    int num_children = get_child_count();
    for( int i = 0; i < num_children; ++i ) {
        AIConsiderationBase* considerationNode = godot::Object::cast_to<AIConsiderationBase>(get_child(i));
        if( considerationNode == nullptr ) continue;
        _score += considerationNode->evaluate();
    }//endfor children

    return _score;
}
