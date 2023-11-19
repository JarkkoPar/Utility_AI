#ifndef UtilityAIDotProductToPositionVector3SearchCriterion_H_INCLUDED
#define UtilityAIDotProductToPositionVector3SearchCriterion_H_INCLUDED 

#include "UtilityAINQSSearchCriteria.h"


namespace godot {

class UtilityAIDotProductToPositionVector3SearchCriterion : public UtilityAINQSSearchCriteria {
    GDCLASS(UtilityAIDotProductToPositionVector3SearchCriterion, UtilityAINQSSearchCriteria)

private:

    Vector3 _dot_product_position_vector;
    double  _filtering_value;
    int     _filtering_rule;

protected:
    static void _bind_methods();
    virtual void _initialize_criterion() override;
public:
    UtilityAIDotProductToPositionVector3SearchCriterion();
    ~UtilityAIDotProductToPositionVector3SearchCriterion();
    
    enum UtilityAIDotProductToPositionVector3SearchCriteriaFilteringRule {
        LessThan = 0,
        LessOrEqual = 1,
        Equal = 2,
        MoreOrEqual = 3,
        MoreThan = 4,
    };
    
    // Getters and setters for attributes.

    void set_dot_product_position_vector( Vector3 dot_product_position_vector );
    Vector3 get_dot_product_position_vector() const;

    
    void set_filtering_value( double filtering_value );
    double get_filtering_value() const;
    
    void set_filtering_rule( int filtering_rule );
    int get_filtering_rule() const;
    
    // Handling methods.

    virtual void apply_criterion( Node* node, bool& filter_out, double& score ) override;

};

}


#endif 
