#ifndef FACET_PRIMITIVES_H
#define FACET_PRIMITIVES_H

#include "facet_types.h"

FacetMesh* facet_primitive_cube(double size_x, double size_y, double size_z);
FacetMesh* facet_primitive_cylinder(double radius, double height, uint32_t segments);
FacetMesh* facet_primitive_sphere(double radius, uint32_t rings, uint32_t sectors);
FacetMesh* facet_primitive_gear(
    double pitch_radius, double thickness, uint32_t teeth,
    double bore_radius, double keyway_width
);

#endif // FACET_PRIMITIVES_H
