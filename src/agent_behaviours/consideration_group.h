#ifndef UtilityAIConsiderationGROUP_H_INCLUDED
#define UtilityAIConsiderationGROUP_H_INCLUDED 

#include "considerations.h"

#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIConsiderationGroup : public UtilityAIConsiderations {
    GDCLASS(UtilityAIConsiderationGroup, UtilityAIConsiderations)

private:

    int _evaluation_method;
    bool _invert_score;
    
protected:
    static void _bind_methods();

public:
    UtilityAIConsiderationGroup();
    ~UtilityAIConsiderationGroup();
    
    
    // Getters and setters for attributes.
    
    void set_evaluation_method( int evaluation_method );
    int  get_evaluation_method() const;

    enum UtilityAIConsiderationGroupEvaluationMethod {
        Sum = 0,
        Min=1,
        Max=2,
        Mean=3,
        Multiply=4,
        FirstNonZero=5,
        //OneMinusScore=6
    };

    void set_invert_score( bool invert_score );
    bool get_invert_score() const;

    // Handling functions.

    virtual float evaluate() override; //UtilityAIAgent* agent, float delta) override;
    
};

}


#endif 
