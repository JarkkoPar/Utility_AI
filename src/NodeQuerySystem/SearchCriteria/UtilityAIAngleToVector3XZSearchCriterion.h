#ifndef UtilityAIAngleToVector3XZSearchCriterion_H_INCLUDED
#define UtilityAIAngleToVector3XZSearchCriterion_H_INCLUDED 

#include "UtilityAINQSSearchCriteria.h"


namespace godot {

class UtilityAIAngleToVector3XZSearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAIAngleToVector3XZSearchCriterion, UtilityAINQSSearchCriteria)

private:
    double _min_angle_degrees;
    double _max_angle_degrees;

    double _min_angle_radians;
    double _max_angle_radians;

    double _span_radians;
    double _one_over_span_radians;

    Vector3 _angle_to_direction_vector;
    Vector2 _xz_angle_vector;

protected:
    static void _bind_methods();
    virtual void _initialize_criterion() override;
public:
    UtilityAIAngleToVector3XZSearchCriterion();
    ~UtilityAIAngleToVector3XZSearchCriterion();
    
    
    // Getters and setters for attributes.

    void set_angle_to_direction_vector( Vector3 angle_to_direction_vector );
    Vector3 get_angle_to_direction_vector() const;


    void set_min_angle_degrees( double min_angle_degrees );
    double get_min_angle_degrees() const;

    void set_max_angle_degrees( double max_angle_degrees );
    double get_max_angle_degrees() const;

    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score ) override;

};

}


#endif 
