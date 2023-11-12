#include "UtilityAINodeQuerySystem.h"
#include <godot_cpp/classes/engine.hpp>
#include "SearchSpaces/UtilityAINQSSearchSpaces.h"

// Not to be used...

using namespace godot;


UtilityAINodeQuerySystem::UtilityAINodeQuerySystem() {

}

UtilityAINodeQuerySystem::~UtilityAINodeQuerySystem() {

}


//void UtilityAINodeQuerySystem::_bind_methods() {
//
//}

// Godot virtuals. 

/**
void UtilityAINodeQuerySystem::_ready() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    if( get_child_count() < 1 ) {
        WARN_PRINT("UtilityAINodeQuerySystem::_ready() - No children added.");
        return;
    }
}


// Getters and setters.
/**

/**/

// Handing methods.

/**
void UtilityAINodeQuerySystem::execute_queries() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    int num_search_spaces = get_child_count();
    if( num_search_spaces < 1 ) return;
    
    // The nodes following the search space node are the evaluation nodes. They are
    // executed in order.
    for( int i = 1; i < num_search_spaces; ++i ) {
        UtilityAINQSSearchSpaces* search_space_node = godot::Object::cast_to<UtilityAINQSSearchSpaces>(get_child(i));
        if( search_space_node == nullptr ) {
            continue; // Not a search space node.
        }
        search_space_node->execute_query();
    } 
}
/**/
    

    