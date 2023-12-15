#ifndef UtilityAIDistanceToNode3DSearchCriterion_H_INCLUDED
#define UtilityAIDistanceToNode3DSearchCriterion_H_INCLUDED 

#include "UtilityAINQSSearchCriteria.h"

#include <godot_cpp/classes/node3d.hpp>


namespace godot {

class UtilityAIDistanceToNode3DSearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAIDistanceToNode3DSearchCriterion, UtilityAINQSSearchCriteria)

private:
    double _min_distance;
    double _max_distance;

    double _min_distance_squared;
    double _max_distance_squared;
    double _span_length;
    double _one_over_span_length;

    Node3D*  _distance_to;

protected:
    static void _bind_methods();
    virtual void _initialize_criterion() override;
public:
    UtilityAIDistanceToNode3DSearchCriterion();
    ~UtilityAIDistanceToNode3DSearchCriterion();
    
    
    // Getters and setters for attributes.

    void set_distance_to( Node3D* distance_to );
    Node3D* get_distance_to() const;


    void set_min_distance( double min_distance );
    double get_min_distance() const;

    void set_max_distance( double max_distance );
    double get_max_distance() const;

    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score ) override;

};

}


#endif 
