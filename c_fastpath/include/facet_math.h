#ifndef FACET_MATH_H
#define FACET_MATH_H

#include "facet_types.h"

#define FACET_EPSILON 1e-9

FacetVec3 facet_vec3_create(double x, double y, double z);
FacetVec3 facet_vec3_add(FacetVec3 a, FacetVec3 b);
FacetVec3 facet_vec3_sub(FacetVec3 a, FacetVec3 b);
FacetVec3 facet_vec3_scale(FacetVec3 v, double s);
FacetVec3 facet_vec3_neg(FacetVec3 v);
double facet_vec3_dot(FacetVec3 a, FacetVec3 b);
FacetVec3 facet_vec3_cross(FacetVec3 a, FacetVec3 b);
double facet_vec3_norm_sq(FacetVec3 v);
double facet_vec3_norm(FacetVec3 v);
FacetVec3 facet_vec3_normalize(FacetVec3 v);
double facet_vec3_dist(FacetVec3 a, FacetVec3 b);
bool facet_vec3_approx_eq(FacetVec3 a, FacetVec3 b, double eps);

FacetPlane facet_plane_from_points(FacetVec3 a, FacetVec3 b, FacetVec3 c);
double facet_plane_dist(FacetPlane pl, FacetVec3 p);
FacetSpatialSide facet_plane_classify_point(FacetPlane pl, FacetVec3 p, double eps);
FacetPlane facet_plane_invert(FacetPlane pl);

double facet_det2x2(double a, double b, double c, double d);
double facet_det3x3(FacetVec3 r0, FacetVec3 r1, FacetVec3 r2);
double facet_orient3d(FacetVec3 a, FacetVec3 b, FacetVec3 c, FacetVec3 d);

bool facet_ray_triangle_intersect(
    FacetVec3 ray_orig, FacetVec3 ray_dir,
    FacetVec3 v0, FacetVec3 v1, FacetVec3 v2,
    double* out_t, double* out_u, double* out_v
);

#endif // FACET_MATH_H
