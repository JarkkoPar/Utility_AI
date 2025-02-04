#include "action_group.h"
#include "action.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIActionGroup::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_action_execution_rule", "action_execution_rule"), &UtilityAIActionGroup::set_action_execution_rule);
    ClassDB::bind_method(D_METHOD("get_action_execution_rule"), &UtilityAIActionGroup::get_action_execution_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "action_execution_rule", PROPERTY_HINT_ENUM, "Sequence:0,PickOneAtRandom:1,IfElse:2,CustomRule:3"), "set_action_execution_rule","get_action_execution_rule");

    ClassDB::bind_method(D_METHOD("set_error_handling_rule", "error_handling_rule"), &UtilityAIActionGroup::set_error_handling_rule);
    ClassDB::bind_method(D_METHOD("get_error_handling_rule"), &UtilityAIActionGroup::get_error_handling_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "error_handling_rule", PROPERTY_HINT_ENUM, "EndExecution:0,ContinueExecution:1"), "set_error_handling_rule","get_error_handling_rule");

    ClassDB::bind_method(D_METHOD("set_current_action_index", "current_action_index"), &UtilityAIActionGroup::set_current_action_index);
    ClassDB::bind_method(D_METHOD("get_current_action_index"), &UtilityAIActionGroup::get_current_action_index);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_action_index", PROPERTY_HINT_RANGE,"0,256,or_greater"), "set_current_action_index","get_current_action_index");

    ClassDB::bind_method(D_METHOD("set_if_else_boolean_value", "if_else_boolean_value"), &UtilityAIActionGroup::set_if_else_boolean_value);
    ClassDB::bind_method(D_METHOD("get_if_else_boolean_value"), &UtilityAIActionGroup::get_if_else_boolean_value);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "if_else_boolean_value", PROPERTY_HINT_NONE), "set_if_else_boolean_value","get_if_else_boolean_value");

    ADD_SIGNAL(MethodInfo("action_failed", PropertyInfo(Variant::OBJECT, "action_node"), PropertyInfo(Variant::OBJECT, "action_group_node")));

}


// Constructor and destructor.

UtilityAIActionGroup::UtilityAIActionGroup() {
    _rnd.instantiate();

    _action_execution_rule = UtilityAIActionGroupExecutionRule::Sequence;
    _error_handling_rule = UtilityAIActionGroupErrorHandlingRule::EndExecution;
    _current_action_index = 0;
    _if_else_boolean_value = true;

    _rnd->set_seed(time(0));
}


UtilityAIActionGroup::~UtilityAIActionGroup() {
}

// Handling functions.

bool UtilityAIActionGroup::start_action() {
    if( get_child_count() <= 0 ) {
        _current_action_index = -1;
        return false;
    }
    switch( _action_execution_rule ) {
        case UtilityAIActionGroupExecutionRule::PickOneAtRandom: {
            _current_action_index = _rnd->randi_range(0, get_child_count() - 1 );
        }
        break;
        case UtilityAIActionGroupExecutionRule::IfElse: {
            if( _if_else_boolean_value ) {
                _current_action_index = 0;
            } else {
                _current_action_index = 1;
            }
        }
        break;
        /*
        case UtilityAIActionGroupExecutionRule::IfPreviousActionFailedElse: {
            if( _if_else_boolean_value ) {
                _current_action_index = 0;
            } else {
                _current_action_index = 1;
            }
        }
        break;
        /**/
        case UtilityAIActionGroupExecutionRule::CustomRule: {
            _current_action_index = -1;
            if( has_method("eval")) {
                call("eval");
            }
        }
        break;
        default: {
            _current_action_index = 0;
        }
        break;
    }
    return true;
}


bool UtilityAIActionGroup::end_action() {
    _current_action_index = -1;
    return true;
}

Node* UtilityAIActionGroup::step_actions() {
    if( _current_action_index >= get_child_count () ) return nullptr;

    // All execution rules must check the current action first if it exists.
    if( _current_action_index > -1 ) {
        // The action has been picked earlier, so check if it has finished.
        Node* current_node = get_child(_current_action_index);
        if( UtilityAIAction* action_node = godot::Object::cast_to<UtilityAIAction>(current_node) ) {
            if( !action_node->get_is_finished() ) return action_node;
            // The action has finished, has it failed?
            if( action_node->get_has_failed() ) {
                // Failed, so fail the group and end/continue based on error handling rule.
                action_node->end_action();
                set_has_failed(true);
                emit_signal("action_failed", action_node, this);
                if( _error_handling_rule == UtilityAIActionGroupErrorHandlingRule::EndExecution) {
                    return nullptr;
                }
            } else {
                // Success, so end and let the stepping continue.
                action_node->end_action();
            }//endif action has failed
        } else {
            if( UtilityAIActionGroup* current_action_group = godot::Object::cast_to<UtilityAIActionGroup>(current_node) ) {
                //WARN_PRINT("UtilityAIActionGroup::step_actions(): Stepping action group " + get_name() + " and proceeding to step a subgroup " + current_action_group->get_name());
                action_node = godot::Object::cast_to<UtilityAIAction>(current_action_group->step_actions());
                if( action_node != nullptr ) return action_node;
                if( current_action_group->get_has_failed() ) {
                    current_action_group->end_action();
                    set_has_failed(true);
                    if( _error_handling_rule == UtilityAIActionGroupErrorHandlingRule::EndExecution) {
                        return nullptr;
                    }
                } else {
                    current_action_group->end_action();
                } //endif action group hs failed
            } // endif is action group node
        } //endif is action node
    } //endif has valid action index

    switch( _action_execution_rule ) {
        case UtilityAIActionGroupExecutionRule::PickOneAtRandom:
        //case UtilityAIActionGroupExecutionRule::IfPreviousActionFailedElse:
        case UtilityAIActionGroupExecutionRule::IfElse: {}
        break;
        case UtilityAIActionGroupExecutionRule::CustomRule: {
            // Re-evaluate, the eval-function should return either a valid
            // action index or one that doesn't work.
            if( has_method("eval")) {
                call("eval");
                if( _current_action_index > -1 )
                {
                    if( UtilityAIAction* action_node = godot::Object::cast_to<UtilityAIAction>(get_child(_current_action_index)) ) {
                        if( action_node->get_is_active() ) {
                            action_node->start_action();
                            return action_node;
                        }
                    } else if(UtilityAIActionGroup* action_group = godot::Object::cast_to<UtilityAIActionGroup>(get_child(_current_action_index)) ) {
                        if( action_group->get_is_active() ) {
                            action_group->start_action();
                            action_node = godot::Object::cast_to<UtilityAIAction>(action_group->step_actions());
                            if( action_node != nullptr ) {
                                action_node->start_action();
                                return action_node;
                            }
                        }
                    }// endif is action or action_group
                }//endif is valid action index
            }
        }
        break;
        default: {
            // Default to a Sequence, where all child nodes are stepped one by one.
            // Try and move to the next step.
            ++_current_action_index;
            while( _current_action_index < get_child_count() ) {
                if( UtilityAIAction* action_node = godot::Object::cast_to<UtilityAIAction>(get_child(_current_action_index)) ) {
                    if( action_node->get_is_active() ) {
                        action_node->start_action();
                        return action_node;
                    }
                } else if(UtilityAIActionGroup* action_group = godot::Object::cast_to<UtilityAIActionGroup>(get_child(_current_action_index)) ) {
                    if( action_group->get_is_active() ) {
                        action_group->start_action();
                        action_node = godot::Object::cast_to<UtilityAIAction>(action_group->step_actions());
                        if( action_node != nullptr ) {
                            action_node->start_action();
                            return action_node;
                        }
                    }
                }// endif is action or action_group
                ++_current_action_index;
            }//endwhile action index in bounds
        }
        break;
    }//end switch action group execution rule

    // No action found.
    return nullptr;
}

// Getters and Setters.

void UtilityAIActionGroup::set_action_execution_rule( int action_execution_rule ) {
    _action_execution_rule = action_execution_rule;
}

int UtilityAIActionGroup::get_action_execution_rule() const {
    return _action_execution_rule;
}

void UtilityAIActionGroup::set_error_handling_rule( int error_handling_rule ) {
    _error_handling_rule = error_handling_rule;
}
int  UtilityAIActionGroup::get_error_handling_rule() const {
    return _error_handling_rule;
}

void UtilityAIActionGroup::set_current_action_index( int current_action_index ) {
    _current_action_index = current_action_index;
}

int  UtilityAIActionGroup::get_current_action_index() const {
    return _current_action_index;
}

void UtilityAIActionGroup::set_if_else_boolean_value( bool if_else_boolean_value ) {
    _if_else_boolean_value = if_else_boolean_value;
}

bool UtilityAIActionGroup::get_if_else_boolean_value() const {
    return _if_else_boolean_value;
}

