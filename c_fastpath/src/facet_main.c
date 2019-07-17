#include "facet_types.h"
#include "facet_math.h"
#include "facet_mesh.h"
#include "facet_bsp.h"
#include "facet_bvh.h"
#include "facet_stl.h"
#include "facet_obj.h"
#include "facet_primitives.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void print_usage(const char* prog) {
    printf("Facet: Verified 3D Constructive Solid Geometry Engine\n");
    printf("Usage:\n");
    printf("  %s info <mesh.stl>              Inspect mesh geometry and manifold topology\n", prog);
    printf("  %s convert <in.stl> <out.obj>    Convert between STL and Wavefront OBJ\n", prog);
    printf("  %s demo <output_dir>             Generate procedural test solids (cube, gear, cylinder)\n", prog);
    printf("  %s boolean <op> <a.stl> <b.stl> <out.stl>  Perform CSG boolean (union/intersect/diff)\n", prog);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    const char* cmd = argv[1];

    if (strcmp(cmd, "info") == 0) {
        if (argc < 3) {
            printf("Error: Missing input file\n");
            return 1;
        }
        FacetMesh* m = facet_stl_read(argv[2]);
        if (!m) {
            printf("Failed to load STL file: %s\n", argv[2]);
            return 1;
        }

        FacetAABB aabb = facet_mesh_compute_aabb(m);
        int32_t chi = 0;
        bool is_manifold = facet_mesh_validate_manifold(m, &chi);

        printf("Mesh Summary: %s\n", argv[2]);
        printf("  Vertices: %zu\n", m->vertex_count);
        printf("  Triangles: %zu\n", m->index_count / 3);
        printf("  Bounding Box: [%.3f, %.3f, %.3f] to [%.3f, %.3f, %.3f]\n",
            aabb.min_pt.x, aabb.min_pt.y, aabb.min_pt.z,
            aabb.max_pt.x, aabb.max_pt.y, aabb.max_pt.z);
        printf("  Euler Characteristic: %d\n", chi);
        printf("  Manifold Topology: %s\n", is_manifold ? "VALID (Closed 2-Manifold)" : "INVALID/NON-MANIFOLD");

        facet_mesh_free(m);
        return 0;
    }

    if (strcmp(cmd, "convert") == 0) {
        if (argc < 4) {
            printf("Error: Missing arguments for convert <in.stl> <out.obj>\n");
            return 1;
        }
        FacetMesh* m = facet_stl_read(argv[2]);
        if (!m) {
            printf("Failed to read input mesh: %s\n", argv[2]);
            return 1;
        }
        bool ok = facet_obj_write(m, argv[3]);
        facet_mesh_free(m);
        if (ok) {
            printf("Successfully converted %s -> %s\n", argv[2], argv[3]);
            return 0;
        }
        return 1;
    }

    if (strcmp(cmd, "demo") == 0) {
        const char* out_dir = (argc >= 3) ? argv[2] : ".";
        char path[512];

        snprintf(path, sizeof(path), "%s/cube.stl", out_dir);
        FacetMesh* cube = facet_primitive_cube(10.0, 10.0, 10.0);
        facet_stl_write_binary(cube, path, "Facet Demo Cube");
        printf("Generated: %s\n", path);
        facet_mesh_free(cube);

        snprintf(path, sizeof(path), "%s/cylinder.stl", out_dir);
        FacetMesh* cyl = facet_primitive_cylinder(5.0, 20.0, 32);
        facet_stl_write_binary(cyl, path, "Facet Demo Cylinder");
        printf("Generated: %s\n", path);
        facet_mesh_free(cyl);

        snprintf(path, sizeof(path), "%s/gear.stl", out_dir);
        FacetMesh* gear = facet_primitive_gear(15.0, 5.0, 16, 3.0, 1.0);
        facet_stl_write_binary(gear, path, "Facet Demo Gear");
        printf("Generated: %s\n", path);
        facet_mesh_free(gear);

        return 0;
    }

    print_usage(argv[0]);
    return 1;
}
