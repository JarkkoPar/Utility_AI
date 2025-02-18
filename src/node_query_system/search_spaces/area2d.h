#ifndef UtilityAIArea2DSearchSpace_H_INCLUDED
#define UtilityAIArea2DSearchSpace_H_INCLUDED

#include "nqs.h"
#include <godot_cpp/classes/area2d.hpp>

namespace godot {

class UtilityAIArea2DSearchSpace : public UtilityAINQSSearchSpaces {
	GDCLASS(UtilityAIArea2DSearchSpace, UtilityAINQSSearchSpaces)

private:
	Area2D *_area2d;

	TypedArray<Area2D> _intersecting_areas;

protected:
	static void _bind_methods();

	virtual void _initialize_search_space() override;
	virtual void _uninitialize_search_space() override;

public:
	UtilityAIArea2DSearchSpace();
	~UtilityAIArea2DSearchSpace();

	void on_area_entered(Area2D *area);
	void on_area_exited(Area2D *area);

	// Getters and setters for attributes.

	void set_area2d(Area2D *area2d);
	Area2D *get_area2d() const;

	void set_intersecting_areas(TypedArray<Area2D> intersecting_areas);
	TypedArray<Area2D> get_intersecting_areas() const;

	virtual TypedArray<Node> get_searchspace_nodes() const override;
};

} //namespace godot

#endif
