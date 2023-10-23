#ifndef UTILITYAIArea3DVisibilitySENSOR_H_INCLUDED
#define UTILITYAIArea3DVisibilitySENSOR_H_INCLUDED 

#include "../UtilityAISensor.h"
#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class UtilityAIArea3DVisibilitySensor : public UtilityAISensor {
    GDCLASS(UtilityAIArea3DVisibilitySensor, UtilityAISensor )

private:
    NodePath _visibility_volume_nodepath;
    Area3D* _visibility_volume_node;

    Vector3 _from_vector;

    TypedArray<Area3D> _entered_areas;
    TypedArray<Area3D> _unoccluded_areas;
    TypedArray<Node3D> _unoccluded_bodies;


    int _expected_number_of_areas_to_track;
    int _expected_number_of_bodies_to_track;
    bool _do_occlusion_test;
    uint32_t  _collision_mask;
    //uint32_t  _entity_mask;

    int _num_entities_found;
    int _max_expected_entities_found;
    double _one_over_max_expected_entities_found;
protected:
    static void _bind_methods();

public:
    UtilityAIArea3DVisibilitySensor();
    ~UtilityAIArea3DVisibilitySensor();

    // Godot virtuals.
    //void _ready();
    //void _notification( int p_what );
   
    
    // Handling functions. 
    virtual void initialize_sensor() override;


    virtual double evaluate_sensor_value() override;

    void on_area_entered(Area3D* area );
    void on_area_exited(Area3D* area );

    // Getters and setters for attributes.
    
    // Configuration values. 

    void set_from_vector3( Vector3 from );
    Vector3 get_from_vector3() const;


    void set_visibility_volume_nodepath( NodePath visibility_volume_nodepath );
    NodePath get_visibility_volume_nodepath() const;

    void set_visibility_volume_node( Area3D* node );
    Area3D* get_visibility_volume_node() const;

    void set_do_occlusion_test( bool do_occlusion_test );
    bool get_do_occlusion_test() const;

    void set_collision_mask( uint32_t collision_mask);
    uint32_t get_collision_mask() const;

    //void set_entity_mask( uint32_t entity_mask);
    //uint32_t get_entity_mask() const;

    void set_max_expected_entities_found( int max_expected_entities_found );
    int  get_max_expected_entities_found() const;
    
    // Debugging / current values.

    void set_num_entities_found( int num_entities_found );
    int  get_num_entities_found() const;
    
    void set_entered_areas( TypedArray<Area3D> entered_areas );
    TypedArray<Area3D> get_entered_areas() const;

    void set_unoccluded_areas( TypedArray<Area3D> unoccluded_areas );
    TypedArray<Area3D> get_unoccluded_areas() const;

    void set_unoccluded_bodies( TypedArray<Node3D> unoccluded_bodies );
    TypedArray<Node3D> get_unoccluded_bodies() const;
};

}


#endif 
