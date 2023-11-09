#ifndef UtilityAIBooleanConsideration_H_INCLUDED
#define UtilityAIBooleanConsideration_H_INCLUDED 

#include "../UtilityAIConsideration.h"


namespace godot {

class UtilityAIBooleanConsideration : public UtilityAIConsideration {
    GDCLASS(UtilityAIBooleanConsideration, UtilityAIConsideration )

private:
    double _true_score_value;
    double _false_score_value;    
protected:
    static void _bind_methods();

    virtual void _evaluate_consideration() override;
public:
    UtilityAIBooleanConsideration();
    ~UtilityAIBooleanConsideration();
    
    
    // Getters and setters for attributes.

    void set_true_score_value( double true_score_value );
    double get_true_score_value() const;

    void set_false_score_value( double false_score_value );
    double get_false_score_value() const;
            
    // Godot virtuals.
    //void _ready();
    //void _notification( int p_what );
   
    // Handling functions.
    
    virtual double sample_activation_curve( double input_value ) const;
};

}


#endif 
