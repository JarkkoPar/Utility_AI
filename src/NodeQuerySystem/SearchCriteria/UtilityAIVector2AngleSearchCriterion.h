#ifndef UtilityAIVector2AngleSearchCriterion_H_INCLUDED
#define UtilityAIVector2AngleSearchCriterion_H_INCLUDED 

#include "UtilityAINQSSearchCriteria.h"


namespace godot {

class UtilityAIVector2AngleSearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAIVector2AngleSearchCriterion, UtilityAINQSSearchCriteria)

private:
    double _min_angle_degrees;
    double _max_angle_degrees;

    double _min_angle_radians;
    double _max_angle_radians;

    double _span_radians;
    double _one_over_span_radians;

    Vector2 _angle_to_direction_vector;

protected:
    static void _bind_methods();
    virtual void _initialize_criterion() override;
public:
    UtilityAIVector2AngleSearchCriterion();
    ~UtilityAIVector2AngleSearchCriterion();
    
    
    // Getters and setters for attributes.

    void set_angle_to_direction_vector( Vector2 angle_to_direction_vector );
    Vector2 get_angle_to_direction_vector() const;


    void set_min_angle_degrees( double min_angle_degrees );
    double get_min_angle_degrees() const;

    void set_max_angle_degrees( double max_angle_degrees );
    double get_max_angle_degrees() const;

    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score ) override;

};

}


#endif 
