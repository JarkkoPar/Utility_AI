#include "UtilityAINodeQuerySystem.h"
#include <godot_cpp/classes/engine.hpp>
#include "SearchSpaces/UtilityAINQSSearchSpaces.h"


using namespace godot;


UtilityAINodeQuerySystem::UtilityAINodeQuerySystem() {

}

UtilityAINodeQuerySystem::~UtilityAINodeQuerySystem() {

}


void UtilityAINodeQuerySystem::_bind_methods() {

}

// Godot virtuals. 

void UtilityAINodeQuerySystem::_ready() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    if( get_child_count() < 1 ) {
        WARN_PRINT("UtilityAINodeQuerySystem::_ready() - No children added.");
        return;
    }
    _search_definition_node = get_child(0);
}


// Getters and setters.

void UtilityAINodeQuerySystem::set_query_results(TypedArray<Node> query_results) {
    _query_results = query_results;
}


TypedArray<Node> UtilityAINodeQuerySystem::get_query_results() const {
    return _query_results;
}


void UtilityAINodeQuerySystem::set_top_n_to_find( int top_n_to_find ) {
    _top_n_to_find = top_n_to_find;
}


int  UtilityAINodeQuerySystem::get_top_n_to_find() const {
    return _top_n_to_find;
}

// Handing methods.

void UtilityAINodeQuerySystem::execute_query() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( get_child_count() < 2 ) return;
    
    _query_results.clear();

    // The first child should be a search space node.
    UtilityAINQSSearchSpaces* search_space_node = godot::Object::cast_to<UtilityAINQSSearchSpaces>(get_child(0));
    if( search_space_node == nullptr ) {
        return; // No search space defined.
    }

    TypedArray<Node> search_space = search_space_node->get_searchspace_nodes();
    if( search_space.size() < 1 ) {
        return; // The search space was empty.
    }

    // The nodes following the search space node are the evaluation nodes. They are
    // executed in order.
    for( int i = 1; i < get_child_count(); ++i ) {

    }
}
    

    