#include "score_based_selector.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/time.hpp>
#include "../performance_monitor_singleton.h"


using namespace godot;

// Method binds.

void UtilityAISTScoreBasedSelector::_bind_methods() {

    //ADD_SUBGROUP("Debugging","");

    //ClassDB::bind_method(D_METHOD("set_total_tick_usec", "total_tick_usec"), &UtilityAISTScoreBasedSelector::set_total_tick_usec);
    //ClassDB::bind_method(D_METHOD("get_total_tick_usec"), &UtilityAISTScoreBasedSelector::get_total_tick_usec);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "total_tick_usec", PROPERTY_HINT_NONE), "set_total_tick_usec","get_total_tick_usec");

    //ClassDB::bind_method(D_METHOD("tick", "user_data", "delta"), &UtilityAISTScoreBasedSelector::tick);
}


// Constructor and destructor.

UtilityAISTScoreBasedSelector::UtilityAISTScoreBasedSelector() {
    
}


UtilityAISTScoreBasedSelector::~UtilityAISTScoreBasedSelector() {
}


// Getters and Setters.






// Handling functions.


UtilityAIStateTreeNodes* UtilityAISTScoreBasedSelector::_tick(Variant user_data, double delta) { 
    // Evaluate the scores and pick the child with the highest
    // score to run.
    int current_child_index = -1;
    double current_highest_score = -99999999.9999;
    for( int i = 0; i < get_child_count(); ++i ) {
        UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(get_child(i));
        if( stnode == nullptr ) {
            continue;
        }
        if( !stnode->get_is_active() ) {
            continue;
        } 
        // Evaluate the node to get its score.
        double score = stnode->evaluate();
        if( score > current_highest_score ) {
            current_child_index = i;
            current_highest_score = score;
        }
    }//endfor children
    if( current_child_index < 0 ) {
        return nullptr;
    }
    
    // The selector will only consider the state tree nodes.
    if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(get_child(current_child_index)) ) {
        return stnode->_tick(user_data, delta);
    }
    return nullptr; // We shouldn't get here. If we do, there were no valid child nodes.
}


// Godot virtuals.
void UtilityAISTScoreBasedSelector::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    reset();
}


