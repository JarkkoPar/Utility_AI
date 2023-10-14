#ifndef UtilityAIBEHAVIOURGROUP_H_INCLUDED
#define UtilityAIBEHAVIOURGROUP_H_INCLUDED 

#include "UtilityAI.h"
//#include "UtilityAIAgent.h"
#include <godot_cpp/classes/node.hpp>

//#include "UtilityAIAction.h"
//#include "UtilityAIActionGroup.h"



namespace godot {

class UtilityAIBehaviourGroup : public UtilityAI {
    GDCLASS(UtilityAIBehaviourGroup, UtilityAI )

private:
    double  _score;
    double  _activation_score;
protected:
    static void _bind_methods();

public:
    UtilityAIBehaviourGroup();
    ~UtilityAIBehaviourGroup();
    
    
    // Getters and setters for attributes.

    void set_activation_score( double score );
    double get_activation_score() const;

    void  set_score( double score );
    double get_score() const;
    
    // Handling functions.

    bool evaluate();

};

}


#endif 
