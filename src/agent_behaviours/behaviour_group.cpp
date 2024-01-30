#include "behaviour_group.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/time.hpp>

#include "consideration.h"
#include "consideration_group.h"


using namespace godot;

// Method binds.

void UtilityAIBehaviourGroup::_bind_methods() {

    ADD_SUBGROUP("Configuration","");
    ClassDB::bind_method(D_METHOD("set_activation_score", "activation_score"), &UtilityAIBehaviourGroup::set_activation_score);
    ClassDB::bind_method(D_METHOD("get_activation_score"), &UtilityAIBehaviourGroup::get_activation_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "activation_score", PROPERTY_HINT_RANGE, "0.0,1.0"), "set_activation_score","get_activation_score");

    ClassDB::bind_method(D_METHOD("set_considerations", "considerations"), &UtilityAIBehaviourGroup::set_considerations);
    ClassDB::bind_method(D_METHOD("get_considerations"), &UtilityAIBehaviourGroup::get_considerations);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "considerations", PROPERTY_HINT_ARRAY_TYPE,vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "UtilityAIConsiderationResources") ), "set_considerations","get_considerations");

    
    ADD_SUBGROUP("Debugging","");
    //ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviourGroup::set_score);
    //ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviourGroup::get_score);
    //ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_RANGE,"0.0,1.0"), "set_score","get_score");

    // Signals.
    ADD_SIGNAL(MethodInfo("behaviour_group_entered"));
    ADD_SIGNAL(MethodInfo("physics_frame_tick", PropertyInfo(Variant::FLOAT, "delta")));
    ADD_SIGNAL(MethodInfo("idle_frame_tick", PropertyInfo(Variant::FLOAT, "delta")));
    ADD_SIGNAL(MethodInfo("behaviour_group_exited"));
}


// Constructor and destructor.

UtilityAIBehaviourGroup::UtilityAIBehaviourGroup() {
    _score = 0.0;
    _activation_score = 0.0;
    
}


UtilityAIBehaviourGroup::~UtilityAIBehaviourGroup() {
}



// Getters and Setters.

void UtilityAIBehaviourGroup::set_activation_score( float activation_score ) {
    _activation_score = activation_score;
}

float UtilityAIBehaviourGroup::get_activation_score() const {
    return _activation_score;
}
/**
void UtilityAIBehaviourGroup::set_score( float score ) {
    _score = score;
}

float UtilityAIBehaviourGroup::get_score() const {
    return _score;
}
/**/

void UtilityAIBehaviourGroup::set_considerations( TypedArray<UtilityAIConsiderationResources> considerations ) {
    _considerations = considerations;
}

TypedArray<UtilityAIConsiderationResources> UtilityAIBehaviourGroup::get_considerations() const {
    return _considerations;
}

// Handling functions.

float UtilityAIBehaviourGroup::evaluate(){ 
    #ifdef DEBUG_ENABLED
    _last_evaluated_timestamp = godot::Time::get_singleton()->get_ticks_usec();
    #endif

    //if( !get_is_active() ) return false;
    //if( Engine::get_singleton()->is_editor_hint() ) return false;
    int num_children = get_child_count();
    if( num_children < 1 ) return 0.0f; 
    
    // For the behaviour groups the considerations are evaluated and
    // compared to the set value to determine if the behaviours
    // within the group should be evaluated.
    _score = 0.0f;
    int num_consideration_nodes_handled = 0;

    bool has_vetoed = false;
    // Evaluate the consideration resources (if any).
    int num_resources = _considerations.size();
    for( int i = 0; i < num_resources; ++i ) {
        UtilityAIConsiderationResources* consideration_resource = godot::Object::cast_to<UtilityAIConsiderationResources>(_considerations[i]);
        if( consideration_resource == nullptr ) {
            continue;
        }
        if( !consideration_resource->get_is_active() ) {
            continue;
        }
        float child_score = consideration_resource->evaluate( has_vetoed, this );
        ++num_consideration_nodes_handled;
        if( has_vetoed ) {
            _score = 0.0f; // A consideration vetoed.
            return _score;
        }
        switch( _evaluation_method ) {
            case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Min: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score < _score ) _score = child_score;
            }
            break;
            case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Max: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score > _score ) _score = child_score;
            }
            break;
            case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Multiply: 
            {
                if( i == 0 ) _score = child_score;
                else _score *= child_score;
                // If after multiplication we are at 0.0, then none of the
                // other considerations will ever change the result, so bail.
                if( _score == 0.0 ) {
                    return 0.0;
                }
            }
            break;
            case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::FirstNonZero: 
            {
                if( child_score > 0.0 ) {
                    _score = child_score;
                    return _score;
                }
            }
            break;
            default: _score += child_score;
        }//end switch evaluation method
    }

    // Evaluate the children.
    //for( int i = 0; i < num_children; ++i ) {
    //    Node* node = get_child(i);
    //    if( node == nullptr ) continue;
    //    UtilityAIConsiderations* considerationsNode = godot::Object::cast_to<UtilityAIConsiderations>(node);
    //    if( considerationsNode == nullptr ) continue;
    for( unsigned int i = 0; i < _num_child_considerations; ++i ) {
        UtilityAIConsiderations* considerationsNode = _child_considerations[i];
        if( !considerationsNode->get_is_active() ) continue;
        float child_score = considerationsNode->evaluate();
        ++num_consideration_nodes_handled;
        if( considerationsNode->get_has_vetoed()){
            _score = 0.0f;
            return _score;//return false; // The consideration vetoed this behaviour group.
        }
        switch( _evaluation_method ) {
            case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Min: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score < _score ) _score = child_score;
            }
            break;
            case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Max: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score > _score ) _score = child_score;
            }
            break;
            case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::Multiply: 
            {
                if( i == 0 ) _score = child_score;
                else _score *= child_score;
                // If after multiplication we are at 0.0, then none of the
                // other considerations will ever change the result, so bail.
                if( _score == 0.0 ) {
                    return 0.0;
                }
            }
            break;
            case UtilityAIConsiderationGroup::UtilityAIConsiderationGroupEvaluationMethod::FirstNonZero: 
            {
                if( child_score > 0.0 ) {
                    _score = child_score;
                    return _score;
                }
            }
            break;
            default: _score += child_score;
        }//end switch evaluation method
    }//endfor children

    //if( num_consideration_nodes_handled == 0 ) return true;

    //return (_score >= _activation_score);
    return _score;
}




