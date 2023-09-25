#ifndef UtilityAIConsideration_H_INCLUDED
#define UtilityAIConsideration_H_INCLUDED 

#include "UtilityAIConsiderations.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/curve.hpp>


namespace godot {

class UtilityAIConsideration : public UtilityAIConsiderations {
    GDCLASS(UtilityAIConsideration, UtilityAIConsiderations )

private:
    Ref<Curve> _activation_curve;
    double     _activation_input_value;
    
protected:
    static void _bind_methods();

public:
    UtilityAIConsideration();
    ~UtilityAIConsideration();
    
    
    // Getters and setters for attributes.

    void set_activation_curve( Ref<Curve> activation_curve );
    Ref<Curve> get_activation_curve() const;

    void set_activation_input_value( double activation_input_value );
    double get_activation_input_value() const;

    /**
            
    // Godot virtuals.
    void _ready();
    void _process(double delta);
    void _physics_process(double delta);

    void _notification(int p_what);
    */

    // Handling functions.

    virtual double evaluate(UtilityAIAgent* agent, double delta) override;
};

}


#endif 
