#include "UtilityAIBTSelector.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTSelector::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_is_reactive", "is_reactive"), &UtilityAIBTSelector::set_is_reactive);
    ClassDB::bind_method(D_METHOD("get_is_reactive"), &UtilityAIBTSelector::get_is_reactive);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_reactive", PROPERTY_HINT_NONE), "set_is_reactive","get_is_reactive");
    

    /**
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTSelector::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTSelector::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

}


// Constructor and destructor.

UtilityAIBTSelector::UtilityAIBTSelector() {
    _current_child_index = 0;
    _is_reactive = true;
}


UtilityAIBTSelector::~UtilityAIBTSelector() {
}

// Handling functions.



// Getters and Setters.


void UtilityAIBTSelector::set_is_reactive( bool is_reactive ) {
    _is_reactive = is_reactive;
}

bool UtilityAIBTSelector::get_is_reactive() const {
    return _is_reactive;
}

/**
void UtilityAIBTSelector::set_score( double score ) {
    _score = score;
}

double UtilityAIBTSelector::get_score() const {
    return _score;
}
*/

int UtilityAIBTSelector::tick() { 
    if( _current_child_index < 0 || _is_reactive ) {
        _current_child_index = 0;
    }

    while( _current_child_index < get_child_count() ) {
        UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(_current_child_index));
        if( btnode != nullptr ) {
            int result = btnode->tick();
            if( result == BT_SUCCESS ) {
                _current_child_index = -1;
                return BT_SUCCESS;
            } else if ( result == BT_RUNNING ) {
                return BT_RUNNING;
            }
        }//endif node was of correct type
        ++_current_child_index;
    }//endwhile children to tick
    _current_child_index = -1;
    return BT_FAILURE;
}


