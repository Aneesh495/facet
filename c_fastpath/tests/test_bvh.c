#include <math.h>
#include "facet_mesh.h"
#include "facet_bvh.h"
#include "facet_primitives.h"
#include "facet_math.h"
#include <stdio.h>
#include <assert.h>

void run_test_bvh(void) {
    printf("[TEST] Running BVH Spatial Index and Ray Intersection Tests...\n");

    FacetMesh* cube = facet_primitive_cube(4.0, 4.0, 4.0);
    FacetBVH* bvh = facet_bvh_create(cube);
    assert(bvh != NULL);

    FacetVec3 ray_orig = facet_vec3_create(0, 0, 10);
    FacetVec3 ray_dir = facet_vec3_create(0, 0, -1);

    double hit_t = 0;
    uint32_t tri_idx = 0;
    bool hit = facet_bvh_ray_query(bvh, cube, ray_orig, ray_dir, &hit_t, &tri_idx);
    assert(hit == true);
    assert(fabs(hit_t - 8.0) < 1e-3); // Cube front face at z = 2.0, ray from z=10 => distance 8

    facet_bvh_free(bvh);
    facet_mesh_free(cube);
    printf("  -> BVH Spatial Index Tests PASSED\n");
}
