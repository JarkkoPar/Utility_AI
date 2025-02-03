#ifndef UTILITYAIArea2DVisibilitySENSOR_H_INCLUDED
#define UTILITYAIArea2DVisibilitySENSOR_H_INCLUDED

#include "../sensor.h"
#include <godot_cpp/classes/area2d.hpp>

namespace godot {

class UtilityAIArea2DVisibilitySensor : public UtilityAISensor {
    GDCLASS(UtilityAIArea2DVisibilitySensor, UtilityAISensor )

private:
    Area2D*     _visibility_volume;
    ObjectID    _cache;

    Vector2 _from_vector;
    Vector2 _offset_vector;

    TypedArray<RID>    _occlusion_test_exclusion_list;
    TypedArray<Area2D> _intersecting_areas;
    TypedArray<Node2D> _intersecting_bodies;
    TypedArray<Area2D> _unoccluded_areas;
    TypedArray<Node2D> _unoccluded_bodies;
    TypedArray<float>  _squared_distances_to_intersecting_areas;
    TypedArray<float>  _squared_distances_to_unoccluded_areas;
    TypedArray<float>  _squared_distances_to_intersecting_bodies;
    TypedArray<float>  _squared_distances_to_unoccluded_bodies;
    int _closest_intersecting_area_index;
    int _closest_intersecting_body_index;
    int _closest_unoccluded_area_index;
    int _closest_unoccluded_body_index;

    int _expected_number_of_areas_to_track;
    int _expected_number_of_bodies_to_track;
    bool _do_occlusion_test;
    uint32_t  _collision_mask;

    int _num_entities_found;
    int _max_expected_entities_found;
    float _one_over_max_expected_entities_found;

    bool _use_owner_global_position;

protected:
    static void _bind_methods();
    void _update_cache();
public:
    UtilityAIArea2DVisibilitySensor();
    ~UtilityAIArea2DVisibilitySensor();

    // Godot virtuals.
    //void _ready();
    //void _notification( int p_what );


    // Handling functions.
    virtual void initialize_sensor() override;
    virtual void uninitialize_sensor() override;


    virtual float evaluate_sensor_value() override;

    void on_area_entered(Area2D* area );
    void on_area_exited(Area2D* area );
    void on_body_entered(Node2D* body );
    void on_body_exited(Node2D* body );

    // Getters and setters for attributes.

    // Configuration values.

    void set_use_owner_global_position( bool use_owner_global_position );
    bool get_use_owner_global_position() const;

    void set_from_vector2( Vector2 from );
    Vector2 get_from_vector2() const;

    void set_offset_vector2( Vector2 offset );
    Vector2 get_offset_vector2() const;

    void set_visibility_volume( Area2D* visibility_volume );
    Area2D* get_visibility_volume() const;

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

    void set_closest_intersecting_body_index( int closest_intersecting_body_index );
    int  get_closest_intersecting_body_index() const;

    void set_closest_unoccluded_area_index( int closest_unoccluded_area_index );
    int  get_closest_unoccluded_area_index() const;

    void set_closest_unoccluded_body_index( int closest_unoccluded_body_index );
    int  get_closest_unoccluded_body_index() const;

    void set_intersecting_areas( TypedArray<Area2D> intersecting_areas );
    TypedArray<Area2D> get_intersecting_areas() const;

    void set_intersecting_bodies( TypedArray<Node2D> intersecting_bodies );
    TypedArray<Node2D> get_intersecting_bodies() const;

    void set_unoccluded_areas( TypedArray<Area2D> unoccluded_areas );
    TypedArray<Area2D> get_unoccluded_areas() const;

    void set_unoccluded_bodies( TypedArray<Node2D> unoccluded_bodies );
    TypedArray<Node2D> get_unoccluded_bodies() const;

    void set_squared_distances_to_intersecting_areas( TypedArray<float> squared_distances_to_intersecting_areas );
    TypedArray<float> get_squared_distances_to_intersecting_areas() const;

    void set_squared_distances_to_intersecting_bodies( TypedArray<float> squared_distances_to_intersecting_bodies );
    TypedArray<float> get_squared_distances_to_intersecting_bodies() const;

    void set_squared_distances_to_unoccluded_areas( TypedArray<float> squared_distances_to_unoccluded_areas );
    TypedArray<float> get_squared_distances_to_unoccluded_areas() const;

    void set_squared_distances_to_unoccluded_bodies( TypedArray<float> squared_distances_to_unoccluded_bodies );
    TypedArray<float> get_squared_distances_to_unoccluded_bodies() const;

};

}


#endif
