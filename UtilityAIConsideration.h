#ifndef UtilityAIConsideration_H_INCLUDED
#define UtilityAIConsideration_H_INCLUDED 

#include "UtilityAIConsiderations.h"
#include "UtilityAISensors.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/curve.hpp>


namespace godot {

class UtilityAIConsideration : public UtilityAIConsiderations {
    GDCLASS(UtilityAIConsideration, UtilityAIConsiderations )

private:
    UtilityAISensors* _input_sensor;
    NodePath          _input_sensor_node_path;
    Ref<Curve>        _activation_curve;
    double            _activation_input_value;
    bool              _has_custom_evaluation_method;
    
protected:
    static void _bind_methods();

public:
    UtilityAIConsideration();
    ~UtilityAIConsideration();
    
    
    // Getters and setters for attributes.

    void set_input_sensor_node_path( NodePath input_sensor_node_path );
    NodePath get_input_sensor_node_path() const;

    void set_activation_curve( Ref<Curve> activation_curve );
    Ref<Curve> get_activation_curve() const;

    void set_activation_input_value( double activation_input_value );
    double get_activation_input_value() const;

            
    // Godot virtuals.
    void _ready();
   
    // Handling functions.

    virtual double evaluate() override;
    virtual double sample_activation_curve( double input_value ) const;
};

}


#endif 
