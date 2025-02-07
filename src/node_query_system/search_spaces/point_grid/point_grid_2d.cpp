#include "point_grid_2d.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/navigation_server2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/world2d.hpp>

using namespace godot;

UtilityAIPointGrid2DSearchSpace::UtilityAIPointGrid2DSearchSpace() {
	_offset_vector = Vector2(0.0, 0.0);
	_grid_size = Vector2(150.0f, 150.0f);
	_point_grid_parent_node = nullptr;
	_use_navigation_mesh_positions = true;
	_navigation_map_rid = RID();
	_point_grid_base_spacing_vector = Vector2(20.0f, 10.0f);
	set_point_grid_lattice_type(UtilityAIPointGrid2DSearchSpaceLatticeType::SQUARE);
	_point_grid_type = UtilityAIPointGrid2DSearchSpaceType::RECTANGLE;
}

UtilityAIPointGrid2DSearchSpace::~UtilityAIPointGrid2DSearchSpace() {
	for (int i = 0; i < _point_grid.size(); ++i) {
		Node2D *node = godot::Object::cast_to<Node2D>(_point_grid[i]);
		memfree(node);
		_point_grid[i] = nullptr;
	} //endfor point grid points
	_point_grid.clear();
	/**
	if( _point_grid_parent_node != nullptr ) {
		memfree(_point_grid_parent_node);
		_point_grid_parent_node = nullptr;
	}
	/**/
}

void UtilityAIPointGrid2DSearchSpace::_bind_methods() {
	ADD_SUBGROUP("Configuration", "");

	ClassDB::bind_method(D_METHOD("set_point_grid_parent_node", "point_grid_parent_node"), &UtilityAIPointGrid2DSearchSpace::set_point_grid_parent_node);
	ClassDB::bind_method(D_METHOD("get_point_grid_parent_node"), &UtilityAIPointGrid2DSearchSpace::get_point_grid_parent_node);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "point_grid_parent_node", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_point_grid_parent_node", "get_point_grid_parent_node");

	ClassDB::bind_method(D_METHOD("set_point_grid_type", "point_grid_type"), &UtilityAIPointGrid2DSearchSpace::set_point_grid_type);
	ClassDB::bind_method(D_METHOD("get_point_grid_type"), &UtilityAIPointGrid2DSearchSpace::get_point_grid_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "point_grid_type", PROPERTY_HINT_ENUM, "Rectangle:0"), "set_point_grid_type", "get_point_grid_type");
	// ,Circle:1

	ClassDB::bind_method(D_METHOD("set_grid_size", "grid_size"), &UtilityAIPointGrid2DSearchSpace::set_grid_size);
	ClassDB::bind_method(D_METHOD("get_grid_size"), &UtilityAIPointGrid2DSearchSpace::get_grid_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "grid_size", PROPERTY_HINT_NONE), "set_grid_size", "get_grid_size");

	ClassDB::bind_method(D_METHOD("set_point_grid_lattice_type", "point_grid_lattice_type"), &UtilityAIPointGrid2DSearchSpace::set_point_grid_lattice_type);
	ClassDB::bind_method(D_METHOD("get_point_grid_lattice_type"), &UtilityAIPointGrid2DSearchSpace::get_point_grid_lattice_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "point_grid_lattice_type", PROPERTY_HINT_ENUM, "Square:0,Triangular:1,CenteredRectangular:2,Rectangular:3,Custom:4"), "set_point_grid_lattice_type", "get_point_grid_lattice_type");

	ClassDB::bind_method(D_METHOD("set_point_grid_base_spacing_vector", "point_grid_base_spacing_vector"), &UtilityAIPointGrid2DSearchSpace::set_point_grid_base_spacing_vector2);
	ClassDB::bind_method(D_METHOD("get_point_grid_base_spacing_vector"), &UtilityAIPointGrid2DSearchSpace::get_point_grid_base_spacing_vector2);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "point_grid_base_spacing_vector", PROPERTY_HINT_NONE), "set_point_grid_base_spacing_vector", "get_point_grid_base_spacing_vector");

	ClassDB::bind_method(D_METHOD("set_point_grid_lattice_vector", "point_grid_lattice_vector"), &UtilityAIPointGrid2DSearchSpace::set_point_grid_lattice_vector2);
	ClassDB::bind_method(D_METHOD("get_point_grid_lattice_vector"), &UtilityAIPointGrid2DSearchSpace::get_point_grid_lattice_vector2);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "point_grid_lattice_vector", PROPERTY_HINT_NONE), "set_point_grid_lattice_vector", "get_point_grid_lattice_vector");

	ClassDB::bind_method(D_METHOD("set_offset_vector", "offset_vector"), &UtilityAIPointGrid2DSearchSpace::set_offset_vector2);
	ClassDB::bind_method(D_METHOD("get_offset_vector"), &UtilityAIPointGrid2DSearchSpace::get_offset_vector2);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "offset_vector", PROPERTY_HINT_NONE), "set_offset_vector", "get_offset_vector");

	ClassDB::bind_method(D_METHOD("set_use_navigation_mesh_positions", "navigation_map_rid"), &UtilityAIPointGrid2DSearchSpace::set_use_navigation_mesh_positions);
	ClassDB::bind_method(D_METHOD("get_use_navigation_mesh_positions"), &UtilityAIPointGrid2DSearchSpace::get_use_navigation_mesh_positions);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_navigation_mesh_positions", PROPERTY_HINT_NONE), "set_use_navigation_mesh_positions", "get_use_navigation_mesh_positions");

	ClassDB::bind_method(D_METHOD("set_navigation_map_rid", "navigation_map_rid"), &UtilityAIPointGrid2DSearchSpace::set_navigation_map_rid);
	ClassDB::bind_method(D_METHOD("get_navigation_map_rid"), &UtilityAIPointGrid2DSearchSpace::get_navigation_map_rid);
	ADD_PROPERTY(PropertyInfo(Variant::RID, "navigation_map_rid", PROPERTY_HINT_NONE), "set_navigation_map_rid", "get_navigation_map_rid");

	ADD_SUBGROUP("Debugging", "");

	ClassDB::bind_method(D_METHOD("set_point_grid", "point_grid"), &UtilityAIPointGrid2DSearchSpace::set_point_grid);
	ClassDB::bind_method(D_METHOD("get_point_grid"), &UtilityAIPointGrid2DSearchSpace::get_point_grid);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "point_grid", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Node2D")), "set_point_grid", "get_point_grid");
}

// Godot virtuals.

void UtilityAIPointGrid2DSearchSpace::_ready() {
	//if( !get_is_active() ) return;
	if (Engine::get_singleton()->is_editor_hint())
		return;
	initialize_search_space();
	//create_point_grid();
}

// Getters and setters.

void UtilityAIPointGrid2DSearchSpace::set_point_grid_type(int point_grid_type) {
	_point_grid_type = point_grid_type;
}

int UtilityAIPointGrid2DSearchSpace::get_point_grid_type() const {
	return _point_grid_type;
}

void UtilityAIPointGrid2DSearchSpace::set_point_grid_lattice_type(int point_grid_lattice_type) {
	_point_grid_lattice_type = point_grid_lattice_type;
	switch (point_grid_lattice_type) {
		case UtilityAIPointGrid2DSearchSpaceLatticeType::SQUARE: {
			_point_grid_base_spacing_vector = Vector2(20.0f, 10.0f);
			_point_grid_lattice_vector = Vector2(10.0f, 0.0f);
		} break;
		case UtilityAIPointGrid2DSearchSpaceLatticeType::TRIANGULAR: {
			_point_grid_base_spacing_vector = Vector2(10.0f, 20.0f);
			_point_grid_lattice_vector = Vector2(-5.0f, 10.0f);
		} break;
		case UtilityAIPointGrid2DSearchSpaceLatticeType::CENTERED_RECTANGULAR: {
			_point_grid_base_spacing_vector = Vector2(20.0f, 10.0f);
			_point_grid_lattice_vector = Vector2(10.0f, 5.0f);
		} break;
		case UtilityAIPointGrid2DSearchSpaceLatticeType::RECTANGULAR: {
			_point_grid_base_spacing_vector = Vector2(20.0f, 5.0f);
			_point_grid_lattice_vector = Vector2(10.0f, 0.0f);
		} break;
		default: {
			// Custom.
		} break;
	}
}

int UtilityAIPointGrid2DSearchSpace::get_point_grid_lattice_type() const {
	return _point_grid_lattice_type;
}

void UtilityAIPointGrid2DSearchSpace::set_point_grid_base_spacing_vector2(Vector2 point_grid_base_spacing_vector) {
	if (_point_grid_base_spacing_vector.x > 0.0f && _point_grid_base_spacing_vector.y > 0.0f) {
		_point_grid_base_spacing_vector = point_grid_base_spacing_vector;
	}
}

Vector2 UtilityAIPointGrid2DSearchSpace::get_point_grid_base_spacing_vector2() const {
	return _point_grid_base_spacing_vector;
}

void UtilityAIPointGrid2DSearchSpace::set_point_grid_lattice_vector2(Vector2 point_grid_lattice_vector) {
	_point_grid_lattice_vector = point_grid_lattice_vector;
}

Vector2 UtilityAIPointGrid2DSearchSpace::get_point_grid_lattice_vector2() const {
	return _point_grid_lattice_vector;
}

void UtilityAIPointGrid2DSearchSpace::set_grid_size(Vector2 grid_size) {
	_grid_size = grid_size;
}

Vector2 UtilityAIPointGrid2DSearchSpace::get_grid_size() const {
	return _grid_size;
}

void UtilityAIPointGrid2DSearchSpace::set_navigation_map_rid(RID navigation_map_rid) {
	_navigation_map_rid = navigation_map_rid;
}

RID UtilityAIPointGrid2DSearchSpace::get_navigation_map_rid() const {
	return _navigation_map_rid;
}

void UtilityAIPointGrid2DSearchSpace::set_use_navigation_mesh_positions(bool use_navigation_mesh_positions) {
	_use_navigation_mesh_positions = use_navigation_mesh_positions;
}

bool UtilityAIPointGrid2DSearchSpace::get_use_navigation_mesh_positions() const {
	return _use_navigation_mesh_positions;
}

TypedArray<Node> UtilityAIPointGrid2DSearchSpace::get_searchspace_nodes() const {
	return _point_grid;
}

void UtilityAIPointGrid2DSearchSpace::set_offset_vector2(Vector2 offset) {
	_offset_vector = offset;
}

Vector2 UtilityAIPointGrid2DSearchSpace::get_offset_vector2() const {
	return _offset_vector;
}

void UtilityAIPointGrid2DSearchSpace::set_point_grid_parent_node(Node2D *point_grid_parent_node) {
	_point_grid_parent_node = point_grid_parent_node;
}

Node2D *UtilityAIPointGrid2DSearchSpace::get_point_grid_parent_node() const {
	return _point_grid_parent_node;
}

void UtilityAIPointGrid2DSearchSpace::set_point_grid(TypedArray<Node2D> point_grid) {
	_point_grid = point_grid;
}

TypedArray<Node2D> UtilityAIPointGrid2DSearchSpace::get_point_grid() const {
	return _point_grid;
}

// Handling methods.

void UtilityAIPointGrid2DSearchSpace::create_point_grid() {
	// This creates the Node2D nodes as hidden child nodes.

	// First create the Vector array for the ideal grid.
	_point_grid_default_positions.clear();
	switch (_point_grid_type) {
		case UtilityAIPointGrid2DSearchSpaceType::CIRCLE: {
		} break;
		default: {
			// Rectangle.
			create_rectangular_point_grid();
		}
	} //end switch point grid type

	// If there is a debug child under the search space node, make duplicates of it
	// under the search space parent node.
	Node2D *template_node = nullptr;
	for (int i = 0; i < get_child_count(); ++i) {
		if (Node2D *dbnode = godot::Object::cast_to<Node2D>(get_child(i))) {
			if (dbnode->get_name() == StringName("DEBUG")) {
				template_node = dbnode;
				break;
			}
		} //endif node3d
	} //endfor childnodes
	if (template_node == nullptr) {
		template_node = memnew(Node2D);
		template_node->set_name("___UTILITYAI_DELETE___");
	}

	// Ensure that score and is_filtered are available for debug.
	template_node->set("score", 0.0f);
	template_node->set("is_filtered", false);

	create_point_grid_nodes(template_node);

	if (template_node->get_name() == StringName("___UTILITYAI_DELETE___")) {
		memdelete(template_node);
		template_node = nullptr;
	}
}

void UtilityAIPointGrid2DSearchSpace::create_point_grid_nodes(Node2D *template_node) {
	for (int i = 0; i < _point_grid_default_positions.size(); ++i) {
		Node2D *new_node = godot::Object::cast_to<Node2D>(template_node->duplicate(15));
		if (new_node == nullptr) {
			ERR_FAIL_MSG("UtilityAIPointGrid2DSearchSpace::create_point_grid_nodes(): Error, could not duplicate template node. Out of memory?");
			return;
		} //endif nullptr
		//new_node->set_script(template_node->get_script());
		_point_grid_parent_node->add_child(new_node); //, false, godot::Node::InternalMode::INTERNAL_MODE_BACK );
		new_node->set_position(_point_grid_default_positions[i] + _offset_vector);
		_point_grid.push_back(new_node);
	} //endfor default positions
}

void UtilityAIPointGrid2DSearchSpace::create_rectangular_point_grid() {
	_point_grid_default_positions.clear();
	float y = -0.5f * _grid_size.y;
	float max_y = 0.5f * _grid_size.y;
	float max_x = 0.5f * _grid_size.x;
	while (_grid_size.y >= 0.0f && y <= max_y) {
		float x = -0.5f * _grid_size.x;
		while (_grid_size.x >= 0.0f && x <= max_x) {
			Vector2 new_point = Vector2(x, y);
			_point_grid_default_positions.push_back(new_point);
			Vector2 lattice_point = new_point + _point_grid_lattice_vector;
			_point_grid_default_positions.push_back(lattice_point);

			x += _point_grid_base_spacing_vector.x;
		} //endwhile y
		y += _point_grid_base_spacing_vector.y;
	} //endwhile x
}

void UtilityAIPointGrid2DSearchSpace::_initialize_search_space() {
	if (_point_grid_parent_node == nullptr)
		return;

	// Create the node3d's for the grid.
	create_point_grid();
	_navigation_map_rid = get_viewport()->get_world_2d()->get_navigation_map();
}

bool UtilityAIPointGrid2DSearchSpace::preprocess_search_space(uint64_t time_limit_timestamp_usec) {
	if (!_use_navigation_mesh_positions || !_navigation_map_rid.is_valid()) {
		return true;
	}
	NavigationServer2D *nav_srv = godot::NavigationServer2D::get_singleton();
	while (_current_preprocessing_node_index < _point_grid_default_positions.size()) {
		Node2D *node = godot::Object::cast_to<Node2D>(_point_grid[_current_preprocessing_node_index]);
		if (node != nullptr) {
			node->set_global_position(nav_srv->map_get_closest_point(_navigation_map_rid, _point_grid_parent_node->get_global_transform().xform(_point_grid_default_positions[_current_preprocessing_node_index])) + _offset_vector);
			//node->set_global_position(nav_srv->map_get_closest_point(_navigation_map_rid,
			//                                                         _point_grid_parent_node->get_global_transform().xform(_point_grid_default_positions[_current_preprocessing_node_index])) + _offset_vector );
		}
		++_current_preprocessing_node_index;
		if (godot::Time::get_singleton()->get_ticks_usec() >= time_limit_timestamp_usec) {
			return false;
		}
	} //endwhile
	return true;
}
