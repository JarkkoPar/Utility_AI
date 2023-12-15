#ifndef UtilityAIMetadataSearchCriterion_H_INCLUDED
#define UtilityAIMetadataSearchCriterion_H_INCLUDED 

#include "nqs.h"

namespace godot {

class UtilityAIMetadataSearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAIMetadataSearchCriterion, UtilityAINQSSearchCriteria)

private:
    StringName _metadata_name;
protected:
    //static void _bind_methods();

public:
    UtilityAIMetadataSearchCriterion();
    ~UtilityAIMetadataSearchCriterion();
    
    
    // Getters and setters for attributes.

    void set_metadata_name( StringName _metadata_name );
    StringName get_metadata_name() const;

    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score ) override;

};

}


#endif 
