#ifndef UtilityAIDistanceToNode2DSearchCriterion_H_INCLUDED
#define UtilityAIDistanceToNode2DSearchCriterion_H_INCLUDED 

#include "nqs.h"

#include <godot_cpp/classes/node2d.hpp>


namespace godot {

class UtilityAIDistanceToNode2DSearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAIDistanceToNode2DSearchCriterion, UtilityAINQSSearchCriteria)

private:
    float _min_distance;
    float _max_distance;

    float _min_distance_squared;
    float _max_distance_squared;
    float _span_length;
    float _one_over_span_length;

    Node2D*  _distance_to;

protected:
    static void _bind_methods();
    virtual void _initialize_criterion() override;
public:
    UtilityAIDistanceToNode2DSearchCriterion();
    ~UtilityAIDistanceToNode2DSearchCriterion();
    
    
    // Getters and setters for attributes.

    void set_distance_to( Node2D* distance_to );
    Node2D* get_distance_to() const;


    void set_min_distance( float min_distance );
    float get_min_distance() const;

    void set_max_distance( float max_distance );
    float get_max_distance() const;

    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, float& score ) override;

};

}


#endif 
