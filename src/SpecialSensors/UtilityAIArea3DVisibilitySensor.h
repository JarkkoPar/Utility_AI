#ifndef UTILITYAIArea3DVisibilitySENSOR_H_INCLUDED
#define UTILITYAIArea3DVisibilitySENSOR_H_INCLUDED 

#include "../UtilityAISensor.h"
#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class UtilityAIArea3DVisibilitySensor : public UtilityAISensor {
    GDCLASS(UtilityAIArea3DVisibilitySensor, UtilityAISensor )

private:
    Area3D* _visibility_volume;

    Vector3 _from_vector;
    Vector3 _offset_vector;

    TypedArray<RID>    _occlusion_test_exclusion_list;
    TypedArray<Area3D> _intersecting_areas;
    TypedArray<Area3D> _unoccluded_areas;
    TypedArray<Node3D> _unoccluded_bodies;
    TypedArray<float>  _squared_distances_to_intersecting_areas;
    TypedArray<float>  _squared_distances_to_unoccluded_areas;
    int _closest_intersecting_area_index;
    int _closest_unoccluded_area_index;

    int _expected_number_of_areas_to_track;
    int _expected_number_of_bodies_to_track;
    bool _do_occlusion_test;
    uint32_t  _collision_mask;

    int _num_entities_found;
    int _max_expected_entities_found;
    double _one_over_max_expected_entities_found;

    bool _use_owner_global_position;
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
    virtual void uninitialize_sensor() override;

    virtual double evaluate_sensor_value() override;

    void on_area_entered(Area3D* area );
    void on_area_exited(Area3D* area );

    // Getters and setters for attributes.
    
    // Configuration values. 

    void set_use_owner_global_position( bool use_owner_global_position );
    bool get_use_owner_global_position() const;

    void set_from_vector3( Vector3 from );
    Vector3 get_from_vector3() const;

    void set_offset_vector3( Vector3 offset );
    Vector3 get_offset_vector3() const;

    void set_visibility_volume( Area3D* visibility_volume );
    Area3D* get_visibility_volume() const;

    void set_do_occlusion_test( bool do_occlusion_test );
    bool get_do_occlusion_test() const;

    void set_collision_mask( uint32_t collision_mask);
    uint32_t get_collision_mask() const;

    void set_max_expected_entities_found( int max_expected_entities_found );
    int  get_max_expected_entities_found() const;

    void set_occlusion_test_exclusion_list( TypedArray<RID> occlusion_test_exclusion_list );
    TypedArray<RID> get_occlusion_test_exclusion_list() const;
    
    // Debugging / current values.

    void set_num_entities_found( int num_entities_found );
    int  get_num_entities_found() const;
    
    void set_closest_intersecting_area_index( int closest_intersecting_area_index );
    int  get_closest_intersecting_area_index() const;

    void set_closest_unoccluded_area_index( int closest_unoccluded_area_index );
    int  get_closest_unoccluded_area_index() const;

    void set_intersecting_areas( TypedArray<Area3D> intersecting_areas );
    TypedArray<Area3D> get_intersecting_areas() const;

    void set_unoccluded_areas( TypedArray<Area3D> unoccluded_areas );
    TypedArray<Area3D> get_unoccluded_areas() const;

    void set_unoccluded_bodies( TypedArray<Node3D> unoccluded_bodies );
    TypedArray<Node3D> get_unoccluded_bodies() const;

    void set_squared_distances_to_intersecting_areas( TypedArray<float> squared_distances_to_intersecting_areas );
    TypedArray<float> get_squared_distances_to_intersecting_areas() const;

    void set_squared_distances_to_unoccluded_areas( TypedArray<float> squared_distances_to_unoccluded_areas );
    TypedArray<float> get_squared_distances_to_unoccluded_areas() const;


};

}


#endif 
