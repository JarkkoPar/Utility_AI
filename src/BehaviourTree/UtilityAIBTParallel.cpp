#include "UtilityAIBTParallel.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTParallel::_bind_methods() {
    
    //ClassDB::bind_method(D_METHOD("set_is_reactive", "is_reactive"), &UtilityAIBTParallel::set_is_reactive);
    //ClassDB::bind_method(D_METHOD("get_is_reactive"), &UtilityAIBTParallel::get_is_reactive);
    //ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_reactive", PROPERTY_HINT_NONE), "set_is_reactive","get_is_reactive");
    
    /*
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBTParallel::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBTParallel::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");
    /**/

}


// Constructor and destructor.

UtilityAIBTParallel::UtilityAIBTParallel() {
    _current_child_index = 0;
    //_is_reactive = true;
}


UtilityAIBTParallel::~UtilityAIBTParallel() {
}

// Handling functions.



// Getters and Setters.

/**
void UtilityAIBTParallel::set_is_reactive( bool is_reactive ) {
    _is_reactive = is_reactive;
}

bool UtilityAIBTParallel::get_is_reactive() const {
    return _is_reactive;
}
/**/

int UtilityAIBTParallel::tick() {
    int parallelresult = BT_SUCCESS;
    for( int i = 0; i < get_child_count(); ++i ) {
        UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i));
        if( btnode != nullptr ) {
            int result = btnode->tick();
            if( result == BT_FAILURE ) {
                parallelresult = BT_FAILURE;
            } else if ( result == BT_RUNNING ) {
                parallelresult = BT_RUNNING;
            }
        }//endif node was of correct type
    }
    return parallelresult;
    /*
    if( _current_child_index < 0 || _is_reactive ) {
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
    /**/
}


