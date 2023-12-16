#include "nodes.h"
#include "../considerations.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIStateTreeNodes::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAIStateTreeNodes::set_evaluation_method);
    ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAIStateTreeNodes::get_evaluation_method);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method","get_evaluation_method");

    ClassDB::bind_method(D_METHOD("set_reset_rule", "reset_rule"), &UtilityAIStateTreeNodes::set_reset_rule);
    ClassDB::bind_method(D_METHOD("get_reset_rule"), &UtilityAIStateTreeNodes::get_reset_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "reset_rule", PROPERTY_HINT_ENUM, "WhenTicked:0,WhenCompleted:1,WhenTickedAfterBeingCompleted:2,Never:3" ), "set_reset_rule","get_reset_rule");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIStateTreeNodes::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIStateTreeNodes::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");

    ClassDB::bind_method(D_METHOD("set_tick_result", "tick_result"), &UtilityAIStateTreeNodes::set_tick_result);
    ClassDB::bind_method(D_METHOD("get_tick_result"), &UtilityAIStateTreeNodes::get_tick_result);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "tick_result", PROPERTY_HINT_ENUM, "Running:0,Success:1,Failure:-1,Skip:-2" ), "set_tick_result","get_tick_result");

    ClassDB::bind_method(D_METHOD("set_internal_status", "internal_status"), &UtilityAIStateTreeNodes::set_internal_status);
    ClassDB::bind_method(D_METHOD("get_internal_status"), &UtilityAIStateTreeNodes::get_internal_status);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "internal_status", PROPERTY_HINT_ENUM, "Unticked:0,Ticked:1,Completed:2" ), "set_internal_status","get_internal_status");

    ClassDB::bind_method(D_METHOD("_tick", "user_data", "delta" ), &UtilityAIStateTreeNodes::tick);

}


// Constructor and destructor.

UtilityAIStateTreeNodes::UtilityAIStateTreeNodes() {
    _score = 0.0;
    _evaluation_method = UtilityAIStateTreeNodesEvaluationMethod::Multiply;
    _invert_score = false;
    _tick_result = ST_SUCCESS;
    _internal_status = ST_INTERNAL_STATUS_UNTICKED;
    _reset_rule = UtilityAIStateTreeNodesResetRule::WHEN_TICKED_AFTER_BEING_COMPLETED;
    _has_reset_rule_changed = false;
}


UtilityAIStateTreeNodes::~UtilityAIStateTreeNodes() {
}


// Getters and Setters.


void UtilityAIStateTreeNodes::set_evaluation_method( int evaluation_method ) {
    _evaluation_method = evaluation_method;
}

int UtilityAIStateTreeNodes::get_evaluation_method() const {
    return _evaluation_method;
}

void UtilityAIStateTreeNodes::set_score( double score ) {
    _score = score;
}


double UtilityAIStateTreeNodes::get_score() const {
    return _score;
}

void UtilityAIStateTreeNodes::set_tick_result( int tick_result ) {
    _tick_result = tick_result;
    if( _tick_result > 1 ) {
        _tick_result = 1;
    } else if (_tick_result < -2 ) {
        _tick_result = -2;
    }
}


int  UtilityAIStateTreeNodes::get_tick_result() const {
    return _tick_result;
}

void UtilityAIStateTreeNodes::set_internal_status( int internal_status ) {
    switch( _reset_rule ) {
        case UtilityAIStateTreeNodesResetRule::WHEN_COMPLETED: {
            if( internal_status == ST_INTERNAL_STATUS_COMPLETED ) {
                //reset_bt_node();
            }
        }
        break;
        case UtilityAIStateTreeNodesResetRule::WHEN_TICKED_AFTER_BEING_COMPLETED: {
            if( _internal_status == ST_INTERNAL_STATUS_COMPLETED &&
                 internal_status == ST_INTERNAL_STATUS_TICKED ) {
                //reset_bt_node();
            }
        }
        break;
        case UtilityAIStateTreeNodesResetRule::WHEN_TICKED: {
            if( internal_status == ST_INTERNAL_STATUS_TICKED && (_internal_status != ST_INTERNAL_STATUS_UNTICKED || _has_reset_rule_changed ) ) {
                //reset_bt_node();
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


int  UtilityAIStateTreeNodes::get_internal_status() const {
    return _internal_status;
}


void UtilityAIStateTreeNodes::set_reset_rule( int reset_rule ) {
    _has_reset_rule_changed = (reset_rule != _reset_rule);
    _reset_rule = reset_rule;
}


int  UtilityAIStateTreeNodes::get_reset_rule() const {
    return _reset_rule;
}

// Handling methods.

void UtilityAIStateTreeNodes::reset() {
    _internal_status = ST_INTERNAL_STATUS_UNTICKED;
    for( int i = 0; i < get_child_count(); ++i ) {
        if( UtilityAIStateTreeNodes* btnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(get_child(i)) ) {
            btnode->reset();
        }
    }
}


double UtilityAIStateTreeNodes::evaluate() {
    if( !get_is_active() ) return 0.0;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0;

    _score = 0.0;
    
    // Evaluate the children.
    int num_children = get_child_count();
    if( num_children < 1 ) return 0.0;
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
            case UtilityAIStateTreeNodesEvaluationMethod::Min: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score < _score ) _score = child_score;
            }
            break;
            case UtilityAIStateTreeNodesEvaluationMethod::Max: 
            {
                if( i == 0 ) _score = child_score;
                if( child_score > _score ) _score = child_score;
            }
            break;
            case UtilityAIStateTreeNodesEvaluationMethod::Multiply: 
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
            case UtilityAIStateTreeNodesEvaluationMethod::FirstNonZero: 
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

    if( _evaluation_method == UtilityAIStateTreeNodesEvaluationMethod::Mean ) {
        _score = _score / ((double)num_children);
    }

    if( _invert_score ) {
        _score = 1.0 - _score;
    }

    return _score;
}


bool UtilityAIStateTreeNodes::on_enter_condition( Variant user_data, double delta ) {
    if( has_method("on_enter_condition")){
        return call("on_enter_condition", user_data, delta );
    }
    return false;
}

UtilityAIStateTreeNodes* UtilityAIStateTreeNodes::tick(Variant user_data, double delta ) { 
    return nullptr;
}


