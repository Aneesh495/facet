#include "facet_mesh.h"
#include "facet_primitives.h"
#include <stdio.h>
#include <assert.h>

void run_test_mesh(void) {
    printf("[TEST] Running Mesh Topology and Euler Tests...\n");

    FacetMesh* cube = facet_primitive_cube(2.0, 2.0, 2.0);
    assert(cube != NULL);
    assert(cube->index_count == 36); // 12 triangles * 3

    int32_t chi = 0;
    bool is_manifold = facet_mesh_validate_manifold(cube, &chi);
    assert(is_manifold == true);
    assert(chi == 2);

    FacetAABB aabb = facet_mesh_compute_aabb(cube);
    assert(aabb.min_pt.x <= -1.0 && aabb.max_pt.x >= 1.0);
    assert(aabb.min_pt.y <= -1.0 && aabb.max_pt.y >= 1.0);
    assert(aabb.min_pt.z <= -1.0 && aabb.max_pt.z >= 1.0);

    facet_mesh_free(cube);
    printf("  -> Mesh Topology and Euler Tests PASSED\n");
}
