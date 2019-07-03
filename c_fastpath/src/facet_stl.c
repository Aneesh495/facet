#include "facet_stl.h"
#include "facet_mesh.h"
#include "facet_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FacetMesh* facet_stl_read(const char* filepath) {
    FILE* f = fopen(filepath, "rb");
    if (!f) return NULL;

    // Check size to distinguish ASCII vs Binary
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (fsize < 84) {
        fclose(f);
        return NULL;
    }

    char header[80];
    if (fread(header, 1, 80, f) != 80) {
        fclose(f);
        return NULL;
    }

    uint32_t num_triangles = 0;
    if (fread(&num_triangles, sizeof(uint32_t), 1, f) != 1) {
        fclose(f);
        return NULL;
    }

    // Binary STL verification: 84 + 50 * num_triangles == fsize
    if (84 + (long)num_triangles * 50 == fsize) {
        FacetMesh* m = facet_mesh_create(num_triangles * 3, num_triangles * 3);
        for (uint32_t i = 0; i < num_triangles; ++i) {
            float buffer[12];
            uint16_t attr = 0;
            if (fread(buffer, sizeof(float), 12, f) != 12) break;
            if (fread(&attr, sizeof(uint16_t), 1, f) != 1) break;

            FacetVec3 v0 = facet_vec3_create(buffer[3], buffer[4], buffer[5]);
            FacetVec3 v1 = facet_vec3_create(buffer[6], buffer[7], buffer[8]);
            FacetVec3 v2 = facet_vec3_create(buffer[9], buffer[10], buffer[11]);

            uint32_t i0 = facet_mesh_add_vertex(m, v0);
            uint32_t i1 = facet_mesh_add_vertex(m, v1);
            uint32_t i2 = facet_mesh_add_vertex(m, v2);
            facet_mesh_add_triangle(m, i0, i1, i2);
        }
        fclose(f);
        facet_mesh_weld_vertices(m, 1e-6);
        facet_mesh_compute_normals(m);
        return m;
    }

    fclose(f);
    return NULL;
}

bool facet_stl_write_ascii(const FacetMesh* mesh, const char* filepath, const char* solid_name) {
    if (!mesh || !filepath) return false;
    FILE* f = fopen(filepath, "w");
    if (!f) return false;

    fprintf(f, "solid %s\n", solid_name ? solid_name : "facet_solid");
    for (size_t i = 0; i < mesh->index_count; i += 3) {
        FacetVec3 v0 = mesh->vertices[mesh->indices[i]];
        FacetVec3 v1 = mesh->vertices[mesh->indices[i + 1]];
        FacetVec3 v2 = mesh->vertices[mesh->indices[i + 2]];

        FacetVec3 fn = facet_vec3_normalize(facet_vec3_cross(
            facet_vec3_sub(v1, v0), facet_vec3_sub(v2, v0)
        ));

        fprintf(f, "  facet normal %.6e %.6e %.6e\n", fn.x, fn.y, fn.z);
        fprintf(f, "    outer loop\n");
        fprintf(f, "      vertex %.6e %.6e %.6e\n", v0.x, v0.y, v0.z);
        fprintf(f, "      vertex %.6e %.6e %.6e\n", v1.x, v1.y, v1.z);
        fprintf(f, "      vertex %.6e %.6e %.6e\n", v2.x, v2.y, v2.z);
        fprintf(f, "    endloop\n");
        fprintf(f, "  endfacet\n");
    }
    fprintf(f, "endsolid %s\n", solid_name ? solid_name : "facet_solid");
    fclose(f);
    return true;
}

bool facet_stl_write_binary(const FacetMesh* mesh, const char* filepath, const char* header_info) {
    if (!mesh || !filepath) return false;
    FILE* f = fopen(filepath, "wb");
    if (!f) return false;

    char header[80] = {0};
    if (header_info) {
        strncpy(header, header_info, 79);
    } else {
        strncpy(header, "Facet Verified 3D Engine Binary STL", 79);
    }
    fwrite(header, 1, 80, f);

    uint32_t num_triangles = (uint32_t)(mesh->index_count / 3);
    fwrite(&num_triangles, sizeof(uint32_t), 1, f);

    for (size_t i = 0; i < mesh->index_count; i += 3) {
        FacetVec3 v0 = mesh->vertices[mesh->indices[i]];
        FacetVec3 v1 = mesh->vertices[mesh->indices[i + 1]];
        FacetVec3 v2 = mesh->vertices[mesh->indices[i + 2]];

        FacetVec3 fn = facet_vec3_normalize(facet_vec3_cross(
            facet_vec3_sub(v1, v0), facet_vec3_sub(v2, v0)
        ));

        float buffer[12];
        buffer[0] = (float)fn.x;  buffer[1] = (float)fn.y;  buffer[2] = (float)fn.z;
        buffer[3] = (float)v0.x;  buffer[4] = (float)v0.y;  buffer[5] = (float)v0.z;
        buffer[6] = (float)v1.x;  buffer[7] = (float)v1.y;  buffer[8] = (float)v1.z;
        buffer[9] = (float)v2.x;  buffer[10] = (float)v2.y; buffer[11] = (float)v2.z;

        fwrite(buffer, sizeof(float), 12, f);
        uint16_t attr = 0;
        fwrite(&attr, sizeof(uint16_t), 1, f);
    }

    fclose(f);
    return true;
}
