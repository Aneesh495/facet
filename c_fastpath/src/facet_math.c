#include "facet_math.h"
#include <math.h>

FacetVec3 facet_vec3_create(double x, double y, double z) {
    FacetVec3 v = { x, y, z };
    return v;
}

FacetVec3 facet_vec3_add(FacetVec3 a, FacetVec3 b) {
    FacetVec3 r = { a.x + b.x, a.y + b.y, a.z + b.z };
    return r;
}

FacetVec3 facet_vec3_sub(FacetVec3 a, FacetVec3 b) {
    FacetVec3 r = { a.x - b.x, a.y - b.y, a.z - b.z };
    return r;
}

FacetVec3 facet_vec3_scale(FacetVec3 v, double s) {
    FacetVec3 r = { v.x * s, v.y * s, v.z * s };
    return r;
}

FacetVec3 facet_vec3_neg(FacetVec3 v) {
    FacetVec3 r = { -v.x, -v.y, -v.z };
    return r;
}

double facet_vec3_dot(FacetVec3 a, FacetVec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

FacetVec3 facet_vec3_cross(FacetVec3 a, FacetVec3 b) {
    FacetVec3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

double facet_vec3_norm_sq(FacetVec3 v) {
    return facet_vec3_dot(v, v);
}

double facet_vec3_norm(FacetVec3 v) {
    return sqrt(facet_vec3_norm_sq(v));
}

FacetVec3 facet_vec3_normalize(FacetVec3 v) {
    double n = facet_vec3_norm(v);
    if (n > 1e-12) {
        return facet_vec3_scale(v, 1.0 / n);
    }
    return v;
}

double facet_vec3_dist(FacetVec3 a, FacetVec3 b) {
    return facet_vec3_norm(facet_vec3_sub(a, b));
}

bool facet_vec3_approx_eq(FacetVec3 a, FacetVec3 b, double eps) {
    return (fabs(a.x - b.x) <= eps) &&
           (fabs(a.y - b.y) <= eps) &&
           (fabs(a.z - b.z) <= eps);
}

FacetPlane facet_plane_from_points(FacetVec3 a, FacetVec3 b, FacetVec3 c) {
    FacetVec3 ab = facet_vec3_sub(b, a);
    FacetVec3 ac = facet_vec3_sub(c, a);
    FacetVec3 n = facet_vec3_normalize(facet_vec3_cross(ab, ac));
    double d = facet_vec3_dot(n, a);
    FacetPlane pl = { n, d };
    return pl;
}

double facet_plane_dist(FacetPlane pl, FacetVec3 p) {
    return facet_vec3_dot(pl.normal, p) - pl.dist;
}

FacetSpatialSide facet_plane_classify_point(FacetPlane pl, FacetVec3 p, double eps) {
    double d = facet_plane_dist(pl, p);
    if (fabs(d) <= eps) {
        return FACET_SIDE_COPLANAR;
    }
    return (d > 0.0) ? FACET_SIDE_FRONT : FACET_SIDE_BACK;
}

FacetPlane facet_plane_invert(FacetPlane pl) {
    FacetPlane r = { facet_vec3_neg(pl.normal), -pl.dist };
    return r;
}

double facet_det2x2(double a, double b, double c, double d) {
    return a * d - b * c;
}

double facet_det3x3(FacetVec3 r0, FacetVec3 r1, FacetVec3 r2) {
    return r0.x * facet_det2x2(r1.y, r1.z, r2.y, r2.z) -
           r0.y * facet_det2x2(r1.x, r1.z, r2.x, r2.z) +
           r0.z * facet_det2x2(r1.x, r1.y, r2.x, r2.y);
}

double facet_orient3d(FacetVec3 a, FacetVec3 b, FacetVec3 c, FacetVec3 d) {
    FacetVec3 ab = facet_vec3_sub(b, a);
    FacetVec3 ac = facet_vec3_sub(c, a);
    FacetVec3 ad = facet_vec3_sub(d, a);
    return facet_vec3_dot(ab, facet_vec3_cross(ac, ad));
}

bool facet_ray_triangle_intersect(
    FacetVec3 ray_orig, FacetVec3 ray_dir,
    FacetVec3 v0, FacetVec3 v1, FacetVec3 v2,
    double* out_t, double* out_u, double* out_v
) {
    FacetVec3 e1 = facet_vec3_sub(v1, v0);
    FacetVec3 e2 = facet_vec3_sub(v2, v0);
    FacetVec3 pvec = facet_vec3_cross(ray_dir, e2);
    double det = facet_vec3_dot(e1, pvec);

    if (fabs(det) < 1e-12) {
        return false;
    }

    double inv_det = 1.0 / det;
    FacetVec3 tvec = facet_vec3_sub(ray_orig, v0);
    double u = facet_vec3_dot(tvec, pvec) * inv_det;
    if (u < 0.0 || u > 1.0) {
        return false;
    }

    FacetVec3 qvec = facet_vec3_cross(tvec, e1);
    double v = facet_vec3_dot(ray_dir, qvec) * inv_det;
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    double t = facet_vec3_dot(e2, qvec) * inv_det;
    if (t < 1e-9) {
        return false;
    }

    if (out_t) *out_t = t;
    if (out_u) *out_u = u;
    if (out_v) *out_v = v;
    return true;
}
