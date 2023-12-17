#include "behaviour_group.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

#include "consideration.h"
#include "consideration_group.h"


using namespace godot;

// Method binds.

void UtilityAIBehaviourGroup::_bind_methods() {

    ADD_SUBGROUP("Configuration","");
    ClassDB::bind_method(D_METHOD("set_activation_score", "activation_score"), &UtilityAIBehaviourGroup::set_activation_score);
    ClassDB::bind_method(D_METHOD("get_activation_score"), &UtilityAIBehaviourGroup::get_activation_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "activation_score", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_activation_score","get_activation_score");

    
    ADD_SUBGROUP("Debugging","");
    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviourGroup::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviourGroup::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_RANGE,"0.0,1.0"), "set_score","get_score");
}


// Constructor and destructor.

UtilityAIBehaviourGroup::UtilityAIBehaviourGroup() {
    _score = 0.0;
    _activation_score = 0.0;
}


UtilityAIBehaviourGroup::~UtilityAIBehaviourGroup() {
}



// Getters and Setters.

void UtilityAIBehaviourGroup::set_activation_score( double activation_score ) {
    _activation_score = activation_score;
}

double UtilityAIBehaviourGroup::get_activation_score() const {
    return _activation_score;
}

void UtilityAIBehaviourGroup::set_score( double score ) {
    _score = score;
}

double UtilityAIBehaviourGroup::get_score() const {
    return _score;
}



// Handling functions.

bool UtilityAIBehaviourGroup::evaluate() { 
    if( !get_is_active() ) return false;
    if( Engine::get_singleton()->is_editor_hint() ) return false;
    int num_children = get_child_count();
    if( num_children < 1 ) return false; 
    
    // For the behaviour groups the considerations are evaluated and
    // compared to the set value to determine if the behaviours
    // within the group should be evaluated.
    _score = 0.0;
    int num_consideration_nodes_handled = 0;

    // Evaluate the children.
    for( int i = 0; i < num_children; ++i ) {
        Node* node = get_child(i);
        if( node == nullptr ) continue;
        UtilityAIConsiderations* considerationsNode = godot::Object::cast_to<UtilityAIConsiderations>(node);
        if( considerationsNode == nullptr ) continue;
        if( !considerationsNode->get_is_active() ) continue;
        _score += considerationsNode->evaluate();
        ++num_consideration_nodes_handled;
        if( considerationsNode->get_has_vetoed()){
            _score = 0.0;
            return false; // The consideration vetoed this behaviour group.
        }
    }//endfor children

    if( num_consideration_nodes_handled == 0 ) return true;

    return (_score >= _activation_score);
}



