#ifndef UtilityAICustomPropertyConsideration_H_INCLUDED
#define UtilityAICustomPropertyConsideration_H_INCLUDED 

#include "../considerations.h"
#include <godot_cpp/classes/curve.hpp>

namespace godot {

class UtilityAICustomPropertyConsideration : public UtilityAIConsiderations {
    GDCLASS(UtilityAICustomPropertyConsideration, UtilityAIConsiderations )

private:
    Node*       _node_with_property;
    StringName  _property_name;
    float      _property_max_value;    
    float      _one_over_property_max_value;
    Variant     _property_variant_value;
    Ref<Curve>  _activation_curve;
protected:
    static void _bind_methods();

public:
    UtilityAICustomPropertyConsideration();
    ~UtilityAICustomPropertyConsideration();
    
    
    // Getters and setters for attributes.

    void set_activation_curve( Ref<Curve> activation_curve );
    Ref<Curve> get_activation_curve() const;

    void set_node_with_property( Node* node_with_property );
    Node* get_node_with_property() const;

    void set_property_max_value( float true_score_value );
    float get_property_max_value() const;

    void set_property_name( StringName property_name );
    StringName get_property_name() const;
            
    // Godot virtuals.
    void _ready() override;
    //void _notification( int p_what );
   
    // Handling functions.
    void initialize_consideration();
    virtual float evaluate() override;
    virtual float sample_activation_curve( float input_value ) const;
    //virtual float sample_activation_curve( float input_value ) const;
};

}


#endif 
