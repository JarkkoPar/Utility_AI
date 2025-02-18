#ifndef UtilityAIPointGrid3DSearchSpaces_H_INCLUDED
#define UtilityAIPointGrid3DSearchSpaces_H_INCLUDED

#include "../nqs.h"
#include <godot_cpp/classes/node3d.hpp>

namespace godot {

class UtilityAIPointGrid3DSearchSpace : public UtilityAINQSSearchSpaces {
	GDCLASS(UtilityAIPointGrid3DSearchSpace, UtilityAINQSSearchSpaces)

public:
	UtilityAIPointGrid3DSearchSpace();
	~UtilityAIPointGrid3DSearchSpace();

	// Godot virtuals.
	void _ready() override;

	// Getters and setters for attributes.

	void set_point_grid_type(int point_grid_type);
	int get_point_grid_type() const;

	void set_point_grid_lattice_type(int point_grid_lattice_type);
	int get_point_grid_lattice_type() const;

	void set_point_grid_lattice_vector3(Vector3 point_grid_lattice_vector);
	Vector3 get_point_grid_lattice_vector3() const;

	void set_point_grid_base_spacing_vector3(Vector3 grid_base_spacing_vector);
	Vector3 get_point_grid_base_spacing_vector3() const;

	void set_navigation_map_rid(RID navigation_map_rid);
	RID get_navigation_map_rid() const;

	void set_offset_vector3(Vector3 offset);
	Vector3 get_offset_vector3() const;

	void set_point_grid_parent_node(Node3D *point_grid_parent_node);
	Node3D *get_point_grid_parent_node() const;

	void set_grid_spacing(Vector3 grid_spacing);
	Vector3 get_grid_spacing() const;

	void set_grid_size(Vector3 grid_size);
	Vector3 get_grid_size() const;

	void set_use_navigation_mesh_positions(bool use_navigation_mesh_positions);
	bool get_use_navigation_mesh_positions() const;

	void set_point_grid(TypedArray<Node3D> point_grid);
	TypedArray<Node3D> get_point_grid() const;

	virtual TypedArray<Node> get_searchspace_nodes() const override;

	// Handling methods.

	virtual void create_point_grid();
	void create_rectangular_point_grid();
	void create_point_grid_nodes(Node3D *template_node);

	enum UtilityAIPointGrid3DSearchSpaceType {
		RECTANGLE = 0,
		CIRCLE = 1,
	};

	enum UtilityAIPointGrid3DSearchSpaceLatticeType {
		SQUARE = 0,
		TRIANGULAR = 1,
		CENTERED_RECTANGULAR = 2,
		RECTANGULAR = 3,
		CUSTOM = 4,
	};

private:
	RID _navigation_map_rid;
	Vector3 _offset_vector;
	bool _use_navigation_mesh_positions;

protected:
	static void _bind_methods();

	virtual void _initialize_search_space() override;
	virtual bool preprocess_search_space(uint64_t time_limit_timestamp_usec) override;

	Vector3 _grid_size;
	Vector3 _point_grid_base_spacing_vector;
	int _point_grid_lattice_type;
	Vector3 _point_grid_lattice_vector;

	int _point_grid_type;
	Node3D *_point_grid_parent_node;
	TypedArray<Node3D> _point_grid;

	std::vector<Vector3> _point_grid_default_positions;
};

} //namespace godot

#endif
