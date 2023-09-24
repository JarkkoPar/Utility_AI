#ifndef UtilityAIConsiderationGROUP_H_INCLUDED
#define UtilityAIConsiderationGROUP_H_INCLUDED 

#include "UtilityAIConsiderationBase.h"

#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAIConsiderationGroup : public UtilityAIConsiderationBase {
    GDCLASS(UtilityAIConsiderationGroup, UtilityAIConsiderationBase)

private:

    int _evaluation_method;
    
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
        FirstNonZero=5
    };

    /**    
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */

    // Handling functions.

    virtual float evaluate() override;
    
};

}


#endif 
