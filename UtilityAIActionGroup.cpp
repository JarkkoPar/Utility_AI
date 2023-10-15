#include "UtilityAIActionGroup.h"
#include "UtilityAIAction.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIActionGroup::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_action_execution_rule", "action_execution_rule"), &UtilityAIActionGroup::set_action_execution_rule);
    ClassDB::bind_method(D_METHOD("get_action_execution_rule"), &UtilityAIActionGroup::get_action_execution_rule);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "action_execution_rule", PROPERTY_HINT_ENUM, "Sequence:0,PickOneAtRandom:1"), "set_action_execution_rule","get_action_execution_rule");
    
    ClassDB::bind_method(D_METHOD("set_current_action_index", "current_action_index"), &UtilityAIActionGroup::set_current_action_index);
    ClassDB::bind_method(D_METHOD("get_current_action_index"), &UtilityAIActionGroup::get_current_action_index);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_action_index", PROPERTY_HINT_RANGE,"-0,256"), "set_current_action_index","get_current_action_index");
    
}


// Constructor and destructor.

UtilityAIActionGroup::UtilityAIActionGroup() {
    _action_execution_rule = UtilityAIActionGroupExecutionRule::Sequence;
    _current_action_index = 0;
}


UtilityAIActionGroup::~UtilityAIActionGroup() {
}

// Handling functions.

bool UtilityAIActionGroup::start_action() {
    if( get_child_count() <= 0 ) return false;
    if( _action_execution_rule == UtilityAIActionGroupExecutionRule::PickOneAtRandom ) {
        RandomNumberGenerator rnd;
        rnd.set_seed(time(0));
        _current_action_index = rnd.randi_range(0, get_child_count() - 1 );
    } else {
        _current_action_index = 0;
    }
    return true;
}


bool UtilityAIActionGroup::end_action() {
    _current_action_index = 0;
    return true;
}

Node* UtilityAIActionGroup::step_actions() {
    if( _current_action_index >= get_child_count () ) return nullptr;

    if( _action_execution_rule == UtilityAIActionGroupExecutionRule::PickOneAtRandom ) {
        // Only one action will be picked at random.
        if( _current_action_index > -1 ) {
            // The action has been picked earlier, so check if it has finished.
            Node* current_node = get_child(_current_action_index);
            UtilityAIAction* current_action_node = godot::Object::cast_to<UtilityAIAction>(current_node);
            if( current_action_node != nullptr ) {
                if( !current_action_node->get_is_finished() ) return current_action_node;
                // The action has finished.
                current_action_node->end_action();
                //current_action_node = nullptr;
            } else {
                UtilityAIActionGroup* current_action_group = godot::Object::cast_to<UtilityAIActionGroup>(current_node);
                if( current_action_group != nullptr ) {
                    //WARN_PRINT("UtilityAIActionGroup::step_actions(): Stepping action group " + get_name() + " and proceeding to step a subgroup " + current_action_group->get_name());
                    current_action_node = godot::Object::cast_to<UtilityAIAction>(current_action_group->step_actions());
                    if( current_action_node != nullptr ) return current_action_node;
                    current_action_group->end_action();
                }
            }        
        } //endif has valid action index
        return nullptr;
    } // endif action group execution rule is pick one at random
    else if( _action_execution_rule == UtilityAIActionGroupExecutionRule::Sequence ) {
        // All child nodes are stepped one by one.

        //WARN_PRINT("UtilityAIActionGroup::step_actions(): Stepping action group " + get_name());
        Node* current_node = get_child(_current_action_index);
        UtilityAIAction* current_action_node = godot::Object::cast_to<UtilityAIAction>(current_node);
        if( current_action_node != nullptr ) {
            //WARN_PRINT("UtilityAIActionGroup::step_actions(): Current action in group " + get_name() + " is not null, and is named " + current_action_node->get_name());

            if( !current_action_node->get_is_finished() ) return current_action_node;
            // The action has finished.
            current_action_node->end_action();
            current_action_node = nullptr;
            //WARN_PRINT("UtilityAIActionGroup::step_actions(): The action just finished.");
        } else {
            UtilityAIActionGroup* current_action_group = godot::Object::cast_to<UtilityAIActionGroup>(current_node);
            if( current_action_group != nullptr ) {
                //WARN_PRINT("UtilityAIActionGroup::step_actions(): Stepping action group " + get_name() + " and proceeding to step a subgroup " + current_action_group->get_name());
        
                current_action_node = godot::Object::cast_to<UtilityAIAction>(current_action_group->step_actions());
                if( current_action_node != nullptr ) return current_action_node;
                current_action_group->end_action();
            }
        }//endif current action node valid
        

        ++_current_action_index;
        while( _current_action_index < get_child_count() ) {
            
            if( current_action_node = godot::Object::cast_to<UtilityAIAction>(get_child(_current_action_index)) ) {
                if( current_action_node->get_is_active() ) {
                    current_action_node->start_action();
                    return current_action_node;
                }
            } else if(UtilityAIActionGroup* action_group = godot::Object::cast_to<UtilityAIActionGroup>(get_child(_current_action_index)) ) {
                if( action_group->get_is_active() ) {
                    action_group->start_action();
                    current_action_node = godot::Object::cast_to<UtilityAIAction>(action_group->step_actions());
                    if( current_action_node != nullptr ) {
                        current_action_node->start_action();
                        return current_action_node;
                    }
                }
            }// endif is action or action_group
            ++_current_action_index;
        }//endwhile action index in bounds
    }//endif action group execution rule is sequence

    return nullptr;
}

// Getters and Setters.

void UtilityAIActionGroup::set_action_execution_rule( int action_execution_rule ) {
    _action_execution_rule = action_execution_rule;
}

int UtilityAIActionGroup::get_action_execution_rule() const {
    return _action_execution_rule;
}

void UtilityAIActionGroup::set_current_action_index( int current_action_index ) {
    _current_action_index = current_action_index;
}

int  UtilityAIActionGroup::get_current_action_index() const {
    return _current_action_index;
}

