#include "UtilityAIBTSequence.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTSequence::_bind_methods() {
    /**
    ClassDB::bind_method(D_METHOD("set_has_vetoed", "has_vetoed"), &UtilityAIBTSequence::set_has_vetoed);
    ClassDB::bind_method(D_METHOD("get_has_vetoed"), &UtilityAIBTSequence::get_has_vetoed);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_vetoed", PROPERTY_HINT_NONE), "set_has_vetoed","get_has_vetoed");
    

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTSequence::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTSequence::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

}


// Constructor and destructor.

UtilityAIBTSequence::UtilityAIBTSequence() {
    _current_child_index = 0;
}


UtilityAIBTSequence::~UtilityAIBTSequence() {
}

// Handling functions.



// Getters and Setters.

/**
void UtilityAIBTSequence::set_has_vetoed( bool has_vetoed ) {
    _has_vetoed = has_vetoed;
}

bool UtilityAIBTSequence::get_has_vetoed() const {
    return _has_vetoed;
}


void UtilityAIBTSequence::set_score( double score ) {
    _score = score;
}

double UtilityAIBTSequence::get_score() const {
    return _score;
}
*/

int UtilityAIBTSequence::tick() {
    if( _current_child_index < 0 ) {
        _current_child_index = 0;
    }

    while( _current_child_index < get_child_count() ) {
        UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(_current_child_index));
        if( btnode != nullptr ) {
            int result = btnode->tick();
            if( result == BT_FAILURE ) {
                _current_child_index = -1;
                return BT_FAILURE;
            } else if ( result == BT_RUNNING ) {
                return BT_RUNNING;
            }
        }//endif node was of correct type
        ++_current_child_index;
    }//endwhile children to tick
    _current_child_index = -1;
    return BT_SUCCESS;
}


