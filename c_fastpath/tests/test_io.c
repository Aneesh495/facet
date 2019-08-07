#include "facet_stl.h"
#include "facet_obj.h"
#include "facet_primitives.h"
#include "facet_mesh.h"
#include <stdio.h>
#include <assert.h>

void run_test_io(void) {
    printf("[TEST] Running STL and Wavefront OBJ IO Tests...\n");

    FacetMesh* cyl = facet_primitive_cylinder(2.0, 5.0, 16);
    const char* tmp_stl = "/tmp/facet_test_io.stl";
    const char* tmp_obj = "/tmp/facet_test_io.obj";

    bool ok_stl = facet_stl_write_binary(cyl, tmp_stl, "Test Cylinder");
    assert(ok_stl == true);

    FacetMesh* read_stl = facet_stl_read(tmp_stl);
    assert(read_stl != NULL);
    assert(read_stl->index_count == cyl->index_count);

    bool ok_obj = facet_obj_write(cyl, tmp_obj);
    assert(ok_obj == true);

    FacetMesh* read_obj = facet_obj_read(tmp_obj);
    assert(read_obj != NULL);
    assert(read_obj->vertex_count == cyl->vertex_count);

    facet_mesh_free(cyl);
    facet_mesh_free(read_stl);
    facet_mesh_free(read_obj);
    printf("  -> STL and OBJ IO Tests PASSED\n");
}
