#include "parallel.h"

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
    //ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta"), &UtilityAIBTParallel::tick);

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

int UtilityAIBTParallel::tick(Variant user_data, float delta) {
    set_internal_status(BT_INTERNAL_STATUS_TICKED);
    //if( _is_first_tick ) {
    //    _is_first_tick = false;
    //    emit_signal("btnode_entered", user_data, delta);
    //}
    int parallelresult = BT_SUCCESS;
    //for( int i = 0; i < get_child_count(); ++i ) {
    //    UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i));
    for( unsigned int i = 0; i < _num_child_btnodes; ++i ) {
        UtilityAIBehaviourTreeNodes* btnode = _child_btnodes[i];
        //if( btnode != nullptr ) {
            if( !btnode->get_is_active() ) {
                continue;
            } 
            int result = btnode->tick(user_data, delta);
            if( result == BT_FAILURE ) {
                parallelresult = BT_FAILURE;
            } else if ( result == BT_RUNNING ) {
                parallelresult = BT_RUNNING;
            }
        //}//endif node was of correct type
    }//endfor btnodes
    //emit_signal("btnode_ticked", user_data, delta);
    if( parallelresult != 0 ) {
        set_internal_status(BT_INTERNAL_STATUS_COMPLETED);
        //emit_signal("btnode_exited", user_data, delta);
    }
    set_tick_result(parallelresult);
    return parallelresult;
}


