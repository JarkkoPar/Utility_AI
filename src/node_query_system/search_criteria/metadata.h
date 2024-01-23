#ifndef UtilityAIMetadataSearchCriterion_H_INCLUDED
#define UtilityAIMetadataSearchCriterion_H_INCLUDED 

#include "nqs.h"

namespace godot {

class UtilityAIMetadataSearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAIMetadataSearchCriterion, UtilityAINQSSearchCriteria)

private:
    StringName _metadata_name;
    Variant    _metadata_value;
protected:
    static void _bind_methods();

public:
    UtilityAIMetadataSearchCriterion();
    ~UtilityAIMetadataSearchCriterion();
    
    
    // Getters and setters for attributes.

    void set_metadata_name( StringName metadata_name );
    StringName get_metadata_name() const;

    void set_metadata_value( Variant metadata_value );
    Variant get_metadata_value() const;

    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, float& score ) override;

};

}


#endif 
