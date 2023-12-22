#include "nodes.h"
#include "../agent_behaviours/considerations.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIStateTreeNodes::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_child_state_selection_rule", "child_state_selection_rule"), &UtilityAIStateTreeNodes::set_child_state_selection_rule);
    ClassDB::bind_method(D_METHOD("get_child_state_selection_rule"), &UtilityAIStateTreeNodes::get_child_state_selection_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "child_state_selection_rule", PROPERTY_HINT_ENUM, "OnEnterConditionMethod:0,UtilityScoring:1" ), "set_child_state_selection_rule","get_child_state_selection_rule");

    ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAIStateTreeNodes::set_evaluation_method);
    ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAIStateTreeNodes::get_evaluation_method);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method","get_evaluation_method");

    ClassDB::bind_method(D_METHOD("set_considerations", "considerations"), &UtilityAIStateTreeNodes::set_considerations);
    ClassDB::bind_method(D_METHOD("get_considerations"), &UtilityAIStateTreeNodes::get_considerations);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "considerations", PROPERTY_HINT_ARRAY_TYPE,vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "UtilityAIConsiderationResources") ), "set_considerations","get_considerations");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIStateTreeNodes::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIStateTreeNodes::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");

    ClassDB::bind_method(D_METHOD("transition_to", "new_state_name", "user_data", "delta" ), &UtilityAIStateTreeNodes::transition_to);

}


// Constructor and destructor.

UtilityAIStateTreeNodes::UtilityAIStateTreeNodes() {
    _score = 0.0;
    _evaluation_method = UtilityAIStateTreeNodesEvaluationMethod::Multiply;
    _invert_score = false;
    _tree_root_node = nullptr;
    _child_state_selection_rule = UtilityAIStateTreeNodeChildStateSelectionRule::ON_ENTER_CONDITION_METHOD;
    _tree_root_node = nullptr;
}


UtilityAIStateTreeNodes::~UtilityAIStateTreeNodes() {
    _tree_root_node = nullptr;
}


// Getters and Setters.

void UtilityAIStateTreeNodes::set_considerations( TypedArray<UtilityAIConsiderationResources> considerations ) {
    _considerations = considerations;
}

TypedArray<UtilityAIConsiderationResources> UtilityAIStateTreeNodes::get_considerations() const {
    return _considerations;
}

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

void UtilityAIStateTreeNodes::set_child_state_selection_rule(int child_state_selection_rule ) {
    _child_state_selection_rule = child_state_selection_rule;
}

int  UtilityAIStateTreeNodes::get_child_state_selection_rule() const {
    return _child_state_selection_rule;
}


Dictionary UtilityAIStateTreeNodes::get_child_nodes_as_dictionary(UtilityAIStateTreeNodes* tree_root_node ) {
    _tree_root_node = tree_root_node;
    Dictionary results;
    for( int i = 0; i < get_child_count(); ++i ) {
        if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(get_child(i)) ) {
            results[stnode->get_name()] = stnode;
            results.merge( stnode->get_child_nodes_as_dictionary(tree_root_node) );
        }
    }
    return results;
}


// Handling methods.

double UtilityAIStateTreeNodes::evaluate() {
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
    return true;
}

void UtilityAIStateTreeNodes::on_enter_state( Variant user_data, double delta ) {
    if( has_method("on_enter_state")){
        call("on_enter_state", user_data, delta );
    }
}

void UtilityAIStateTreeNodes::on_exit_state( Variant user_data, double delta ) {
    if( has_method("on_exit_state")){
        call("on_exit_state", user_data, delta );
    }
}


void UtilityAIStateTreeNodes::on_tick( Variant user_data, double delta ) {
    if( has_method("on_tick")){
        call("on_tick", user_data, delta );
    }
}

void UtilityAIStateTreeNodes::transition_to( godot::String new_state_name, Variant user_data, double delta ) {
    if( _tree_root_node == nullptr ) {
        return;
    }
    _tree_root_node->transition_to(new_state_name, user_data, delta);
}


UtilityAIStateTreeNodes* UtilityAIStateTreeNodes::evaluate_state_activation( Variant user_data, double delta ) {
    unsigned int num_state_tree_childs = 0;

    if( get_child_state_selection_rule() == UtilityAIStateTreeNodeChildStateSelectionRule::ON_ENTER_CONDITION_METHOD ) {
        // Childs are evaluated by using the user-defined on_enter_condition method.
        for( int i = 0; i < get_child_count(); ++i ) {
            if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(get_child(i)) ) {
                if( !stnode->get_is_active() ) {
                    continue;
                } 

                ++num_state_tree_childs;
                if( !stnode->on_enter_condition(user_data, delta) ) {
                    continue;
                }
            
                if( UtilityAIStateTreeNodes* result = stnode->evaluate_state_activation(user_data, delta) ) {
                    return result;
                }//endif result is not nullptr
            }//endif valid node type
        }//endfor child nodes
    } else {
        // Childs are evaluated by using Utility-based scoring.
        UtilityAIStateTreeNodes* highest_scoring_state_to_activate;
        double highest_score = -9999999.9999;
        for( int i = 0; i < get_child_count(); ++i ) {
            if( UtilityAIStateTreeNodes* stnode = godot::Object::cast_to<UtilityAIStateTreeNodes>(get_child(i)) ) {
                if( !stnode->get_is_active() ) {
                    continue;
                }

                ++num_state_tree_childs;
                double score = stnode->evaluate();
                if( score > highest_score ) {
                    if( UtilityAIStateTreeNodes* result = stnode->evaluate_state_activation(user_data, delta) ) {
                        highest_score = score;
                        highest_scoring_state_to_activate = result;
                    }//endif result is not nullptr
                }//endif score is higher than current highest
            
                
            }//endif valid node type
        }//endfor child nodes
        // Return the highest scoring state that can activate.
        if( highest_scoring_state_to_activate != nullptr ) {
            return highest_scoring_state_to_activate;
        }
    }//endif state selection method

    
    if( num_state_tree_childs > 0 ) {
        return nullptr;
    }
    return this; // This has no state tree children, so it is a leaf node.
}



