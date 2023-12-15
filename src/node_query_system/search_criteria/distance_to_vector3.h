#ifndef UtilityAIDistanceToVector3SearchCriterion_H_INCLUDED
#define UtilityAIDistanceToVector3SearchCriterion_H_INCLUDED 

#include "nqs.h"


namespace godot {

class UtilityAIDistanceToVector3SearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAIDistanceToVector3SearchCriterion, UtilityAINQSSearchCriteria)

private:
    double _min_distance;
    double _max_distance;

    double _min_distance_squared;
    double _max_distance_squared;
    double _span_length;
    double _one_over_span_length;

    Vector3 _distance_to_vector;

protected:
    static void _bind_methods();
    virtual void _initialize_criterion() override;
public:
    UtilityAIDistanceToVector3SearchCriterion();
    ~UtilityAIDistanceToVector3SearchCriterion();
    
    
    // Getters and setters for attributes.

    void set_distance_to_vector( Vector3 distance_to_vector );
    Vector3 get_distance_to_vector() const;


    void set_min_distance( double min_distance );
    double get_min_distance() const;

    void set_max_distance( double max_distance );
    double get_max_distance() const;

    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score ) override;

};

}


#endif 
