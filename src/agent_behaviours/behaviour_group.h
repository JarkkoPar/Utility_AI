#ifndef UtilityAIBEHAVIOURGROUP_H_INCLUDED
#define UtilityAIBEHAVIOURGROUP_H_INCLUDED 

#include "utility_ai.h"
#include "agent.h"
#include <godot_cpp/classes/node.hpp>
#include "resources/considerations/consideration_resources.h"



namespace godot {

class UtilityAIBehaviourGroup : public UtilityAI {
    GDCLASS(UtilityAIBehaviourGroup, UtilityAI )

private:
    double  _score;
    double  _activation_score;
    TypedArray<UtilityAIConsiderationResources> _considerations;
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

    void set_considerations( TypedArray<UtilityAIConsiderationResources> considerations );
    TypedArray<UtilityAIConsiderationResources> get_considerations() const;

    
    // Handling functions.

    bool evaluate();//UtilityAIAgent* agent);

};

}


#endif 
