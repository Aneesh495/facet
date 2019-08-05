#include "facet_bsp.h"
#include "facet_primitives.h"
#include "facet_mesh.h"
#include <stdio.h>
#include <assert.h>

void run_test_bsp(void) {
    printf("[TEST] Running BSP Tree and CSG Boolean Tests...\n");

    FacetMesh* a = facet_primitive_cube(2.0, 2.0, 2.0);
    FacetMesh* b = facet_primitive_cube(2.0, 2.0, 2.0);

    FacetMesh* res = facet_bsp_boolean(a, b, FACET_CSG_UNION);
    assert(res != NULL);
    assert(res->vertex_count > 0);
    assert(res->index_count > 0);

    facet_mesh_free(a);
    facet_mesh_free(b);
    facet_mesh_free(res);
    printf("  -> BSP Tree and CSG Boolean Tests PASSED\n");
}
