#ifndef UTILITY_AI_CONSIDERATION_RESOURCE_H_INCLUDED
#define UTILITY_AI_CONSIDERATION_RESOURCE_H_INCLUDED

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/curve.hpp>
#include "consideration_resources.h"
#include "../../agent_behaviours/sensors.h"

namespace godot {

class UtilityAIConsiderationResource : public UtilityAIConsiderationResources {
    GDCLASS(UtilityAIConsiderationResource, UtilityAIConsiderationResources )

private:
    bool                _is_active;
    Ref<Curve>          _activation_curve;
    UtilityAISensors*   _input_sensor;
    NodePath            _input_sensor_nodepath;
protected:
    static void _bind_methods();

public:
    UtilityAIConsiderationResource();
    ~UtilityAIConsiderationResource();
    
    
    // Getters and setters for attributes.
    /**/
    //void  set_is_active( bool is_active );
    //bool  get_is_active() const;

    //void set_input_sensor( UtilityAISensors* input_sensor );
    //UtilityAISensors* get_input_sensor() const;

    void set_input_sensor_nodepath( NodePath input_sensor_nodepath );
    NodePath get_input_sensor_nodepath() const;


    void set_activation_curve( Ref<Curve> activation_curve );
    Ref<Curve> get_activation_curve() const;

    /**
    void set_node_with_property( Node* node_with_property );
    Node* get_node_with_property() const;

    void set_property_max_value( double true_score_value );
    double get_property_max_value() const;

    void set_property_name( StringName property_name );
    StringName get_property_name() const;
    /**/     
    // Godot virtuals.
    //void _ready();
    //void _notification( int p_what );
   
    // Handling functions.
    // Handling functions.
    
    virtual double evaluate() override;
    virtual double sample_activation_curve( double input_value ) const;

    //void initialize_consideration();
    //virtual double evaluate() override;
    //virtual double sample_activation_curve( double input_value ) const;
    //virtual double sample_activation_curve( double input_value ) const;
};

}


#endif 

