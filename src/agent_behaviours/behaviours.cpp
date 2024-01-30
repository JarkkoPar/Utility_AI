#include "behaviours.h"

using namespace godot;


void UtilityAIBehaviours::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_evaluation_method", "evaluation_method"), &UtilityAIBehaviours::set_evaluation_method);
    ClassDB::bind_method(D_METHOD("get_evaluation_method"), &UtilityAIBehaviours::get_evaluation_method);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "evaluation_method", PROPERTY_HINT_ENUM, "Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5"), "set_evaluation_method","get_evaluation_method");


    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviours::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviours::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_RANGE,"-100.0,100.0"), "set_score","get_score");
}

// Godot virtuals.

void UtilityAIBehaviours::_notification(int p_what) {

    if( p_what == NOTIFICATION_CHILD_ORDER_CHANGED ) {
        _child_considerations.clear();
        _child_behaviours.clear();
        int num_children = get_child_count();
        for( int i = 0; i < num_children; ++i ) {
            if( UtilityAIConsiderations* cons = godot::Object::cast_to<UtilityAIConsiderations>(get_child(i))) {
                _child_considerations.push_back(cons);
            }
            else if( UtilityAIBehaviours* beh = godot::Object::cast_to<UtilityAIBehaviours>(get_child(i))) {
                _child_behaviours.push_back(beh);
            }
        }//endfor child nodes
        _num_child_considerations = (unsigned int)_child_considerations.size();
        _num_child_behaviours = (unsigned int)_child_behaviours.size();
    }
 }


// Getters and setters.

void UtilityAIBehaviours::set_evaluation_method( int evaluation_method ) {
    _evaluation_method = evaluation_method;
}

int UtilityAIBehaviours::get_evaluation_method() const {
    return _evaluation_method;
}


