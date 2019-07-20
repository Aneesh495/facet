#include "facet_math.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

void run_test_math(void) {
    printf("[TEST] Running Vector and Determinant Math Tests...\n");

    FacetVec3 v1 = facet_vec3_create(1.0, 2.0, 3.0);
    FacetVec3 v2 = facet_vec3_create(4.0, 5.0, 6.0);

    FacetVec3 v_add = facet_vec3_add(v1, v2);
    assert(fabs(v_add.x - 5.0) < 1e-9);
    assert(fabs(v_add.y - 7.0) < 1e-9);
    assert(fabs(v_add.z - 9.0) < 1e-9);

    double dot = facet_vec3_dot(v1, v2);
    assert(fabs(dot - 32.0) < 1e-9);

    FacetVec3 cross = facet_vec3_cross(v1, v2);
    // (1,2,3) x (4,5,6) = (-3, 6, -3)
    assert(fabs(cross.x - (-3.0)) < 1e-9);
    assert(fabs(cross.y - 6.0) < 1e-9);
    assert(fabs(cross.z - (-3.0)) < 1e-9);

    // Orientation determinant of standard unit tetrahedron
    FacetVec3 a = facet_vec3_create(0, 0, 0);
    FacetVec3 b = facet_vec3_create(1, 0, 0);
    FacetVec3 c = facet_vec3_create(0, 1, 0);
    FacetVec3 d = facet_vec3_create(0, 0, 1);

    double orient = facet_orient3d(a, b, c, d);
    assert(orient > 0.0);

    printf("  -> Vector and Determinant Tests PASSED\n");
}
