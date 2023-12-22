#include "nodes.h"
#include "../agent_behaviours/considerations.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBehaviourTreeNodes::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIBehaviourTreeNodes::set_reset_rule);
    ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIBehaviourTreeNodes::get_reset_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");
    
    ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAIBehaviourTreeNodes::set_evaluation_method);
    ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAIBehaviourTreeNodes::get_evaluation_method);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method","get_evaluation_method");

    ClassDB::bind_method(D_METHOD("set_considerations", "considerations"), &UtilityAIBehaviourTreeNodes::set_considerations);
    ClassDB::bind_method(D_METHOD("get_considerations"), &UtilityAIBehaviourTreeNodes::get_considerations);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "considerations", PROPERTY_HINT_ARRAY_TYPE,vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "UtilityAIConsiderationResources") ), "set_considerations","get_considerations");


    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviourTreeNodes::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviourTreeNodes::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");

    ClassDB::bind_method(D_METHOD("set_tick_result", "tick_result"), &UtilityAIBehaviourTreeNodes::set_tick_result);
    ClassDB::bind_method(D_METHOD("get_tick_result"), &UtilityAIBehaviourTreeNodes::get_tick_result);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "tick_result", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1,Skip:-2" ), "set_tick_result","get_tick_result");

    ClassDB::bind_method(D_METHOD("set_internal_status", "internal_status"), &UtilityAIBehaviourTreeNodes::set_internal_status);
    ClassDB::bind_method(D_METHOD("get_internal_status"), &UtilityAIBehaviourTreeNodes::get_internal_status);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "internal_status", PROPERTY_HINT_ENUM, "Unticked:0,Ticked:1,Completed:2" ), "set_internal_status","get_internal_status");

    ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta" ), &UtilityAIBehaviourTreeNodes::tick);

}


// Constructor and destructor.

UtilityAIBehaviourTreeNodes::UtilityAIBehaviourTreeNodes() {
    _score = 0.0;
    _evaluation_method = UtilityAIBehaviourTreeNodesEvaluationMethod::Multiply;
    _invert_score = false;
    _tick_result = BT_SUCCESS;
    _internal_status = BT_INTERNAL_STATUS_UNTICKED;
    _reset_rule = UtilityAIBehaviourTreeNodesResetRule::WHEN_TICKED_AFTER_BEING_COMPLETED;
    _has_reset_rule_changed = false;
}


UtilityAIBehaviourTreeNodes::~UtilityAIBehaviourTreeNodes() {
}


// Getters and Setters.


void UtilityAIBehaviourTreeNodes::set_evaluation_method( int evaluation_method ) {
    _evaluation_method = evaluation_method;
}

int UtilityAIBehaviourTreeNodes::get_evaluation_method() const {
    return _evaluation_method;
}

void UtilityAIBehaviourTreeNodes::set_score( double score ) {
    _score = score;
}


double UtilityAIBehaviourTreeNodes::get_score() const {
    return _score;
}

void UtilityAIBehaviourTreeNodes::set_tick_result( int tick_result ) {
    _tick_result = tick_result;
    if( _tick_result > 1 ) {
        _tick_result = 1;
    } else if (_tick_result < -2 ) {
        _tick_result = -2;
    }
}


int  UtilityAIBehaviourTreeNodes::get_tick_result() const {
    return _tick_result;
}

void UtilityAIBehaviourTreeNodes::set_internal_status( int internal_status ) {
    switch( _reset_rule ) {
        case UtilityAIBehaviourTreeNodesResetRule::WHEN_COMPLETED: {
            if( internal_status == BT_INTERNAL_STATUS_COMPLETED ) {
                reset_bt_node();
            }
        }
        break;
        case UtilityAIBehaviourTreeNodesResetRule::WHEN_TICKED_AFTER_BEING_COMPLETED: {
            if( _internal_status == BT_INTERNAL_STATUS_COMPLETED &&
                 internal_status == BT_INTERNAL_STATUS_TICKED ) {
                reset_bt_node();
            }
        }
        break;
        case UtilityAIBehaviourTreeNodesResetRule::WHEN_TICKED: {
            if( internal_status == BT_INTERNAL_STATUS_TICKED && (_internal_status != BT_INTERNAL_STATUS_UNTICKED || _has_reset_rule_changed ) ) {
                reset_bt_node();
            }
        }
        break;
        default: {

        }
        break;
    }
   
    _internal_status = internal_status;
    _has_reset_rule_changed = false;
}


int  UtilityAIBehaviourTreeNodes::get_internal_status() const {
    return _internal_status;
}


void UtilityAIBehaviourTreeNodes::set_reset_rule( int reset_rule ) {
    _has_reset_rule_changed = (reset_rule != _reset_rule);
    _reset_rule = reset_rule;
}


int  UtilityAIBehaviourTreeNodes::get_reset_rule() const {
    return _reset_rule;
}

void UtilityAIBehaviourTreeNodes::set_considerations( TypedArray<UtilityAIConsiderationResources> considerations ) {
    _considerations = considerations;
}

TypedArray<UtilityAIConsiderationResources> UtilityAIBehaviourTreeNodes::get_considerations() const {
    return _considerations;
}


// Handling methods.

void UtilityAIBehaviourTreeNodes::reset() {
    _internal_status = BT_INTERNAL_STATUS_UNTICKED;
    for( int i = 0; i < get_child_count(); ++i ) {
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i)) ) {
            btnode->reset();
        }
    }
}

/**
void UtilityAIBehaviourTreeNodes::reset_for_looping() {
    _internal_status = BT_INTERNAL_STATUS_UNTICKED;
    for( int i = 0; i < get_child_count(); ++i ) {
        if( UtilityAIBehaviourTreeNodes* btnode = godot::Object::cast_to<UtilityAIBehaviourTreeNodes>(get_child(i)) ) {
            btnode->reset_for_looping();
        }
    }
}
/**/

double UtilityAIBehaviourTreeNodes::evaluate() {
    if( !get_is_active() ) return 0.0;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0;

    _score = 0.0;
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
        double score = consideration_resource->evaluate( has_vetoed, this );
        if( has_vetoed ) {
            _score = 0.0;
            return 0.0; // A consideration vetoed.
        }
        _score += score;
    }
    
    // Evaluate the children.
    int num_children = get_child_count();
    if( num_children < 1 && num_resources < 1 ) return 0.0;
    double child_score = 0.0;
    for( int i = 0; i < num_children; ++i ) {
        Node* node = get_child(i);
        if( node == nullptr ) continue;
        UtilityAIConsiderations* considerationNode = godot::Object::cast_to<UtilityAIConsiderations>(node);
        if( considerationNode == nullptr ) continue;
        if( !considerationNode->get_is_active() ) continue;
        child_score = considerationNode->evaluate();
        if( considerationNode->get_has_vetoed()) {
            _score = 0.0;
            return 0.0; // Veto zeroes out the score for the entire group.
        }

        switch( _evaluation_method ) {
            case UtilityAIBehaviourTreeNodesEvaluationMethod::Min: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score < _score ) _score = child_score;
            }
            break;
            case UtilityAIBehaviourTreeNodesEvaluationMethod::Max: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score > _score ) _score = child_score;
            }
            break;
            case UtilityAIBehaviourTreeNodesEvaluationMethod::Multiply: 
            {
                if( i == 0 ) _score = child_score;
                else _score *= child_score;
                // If after multiplication we are at 0.0, then none of the
                // other considerations will ever change the result, so bail.
                if( _score == 0.0 ) {
                    if( _invert_score ) {
                        _score = 1.0;
                        return 1.0;
                    }
                    _score = 0.0;
                    return 0.0;
                }
            }
            break;
            case UtilityAIBehaviourTreeNodesEvaluationMethod::FirstNonZero: 
            {
                if( child_score > 0.0 ) {
                    if( _invert_score ) {
                        _score = 1.0 - child_score;
                    } else {
                        _score = child_score;
                    }
                    return _score;
                }
            }
            break;
            default: _score += child_score;
        }//end switch evaluation method
        
    }//endfor children

    if( _evaluation_method == UtilityAIBehaviourTreeNodesEvaluationMethod::Mean ) {
        _score = _score / ((double)num_children);
    }

    if( _invert_score ) {
        _score = 1.0 - _score;
    }

    return _score;
}


int UtilityAIBehaviourTreeNodes::tick(Variant user_data, double delta ) { 
    return 0;
}


