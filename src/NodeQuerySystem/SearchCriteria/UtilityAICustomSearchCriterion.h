#ifndef UtilityAICustomSearchCriterion_H_INCLUDED
#define UtilityAICustomSearchCriterion_H_INCLUDED 

#include "UtilityAISearchCriteria.h"

namespace godot {

class UtilityAICustomSearchCriterion : public UtilityAISearchCriteria {
    GDCLASS(UtilityAICustomSearchCriterion, UtilityAISearchCriteria)

private:
    
protected:
    //static void _bind_methods();

public:
    UtilityAICustomSearchCriterion();
    ~UtilityAICustomSearchCriterion();
    
    
    // Getters and setters for attributes.


    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score ) override;

};

}


#endif 
