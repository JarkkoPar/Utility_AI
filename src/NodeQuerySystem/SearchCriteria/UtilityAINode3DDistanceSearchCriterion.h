#ifndef UtilityAINode3DDistanceSearchCriterion_H_INCLUDED
#define UtilityAINode3DDistanceSearchCriterion_H_INCLUDED 

#include "UtilityAINQSSearchCriteria.h"

#include <godot_cpp/classes/node3d.hpp>


namespace godot {

class UtilityAINode3DDistanceSearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAINode3DDistanceSearchCriterion, UtilityAINQSSearchCriteria)

private:
    double _min_distance;
    double _max_distance;

    double _min_distance_squared;
    double _max_distance_squared;
    double _span_length;
    double _one_over_span_length;

    NodePath _distance_to_nodepath;
    Node3D*  _distance_to_node;

protected:
    static void _bind_methods();

public:
    UtilityAINode3DDistanceSearchCriterion();
    ~UtilityAINode3DDistanceSearchCriterion();
    
    
    // Getters and setters for attributes.

    void set_distance_to_nodepath( NodePath distance_to_nodepath );
    NodePath get_distance_to_nodepath() const;


    void set_min_distance( double min_distance );
    double get_min_distance() const;

    void set_max_distance( double max_distance );
    double get_max_distance() const;

    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score ) override;

};

}


#endif 
