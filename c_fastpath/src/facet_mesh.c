#include "facet_mesh.h"
#include "facet_math.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

FacetMesh* facet_mesh_create(size_t initial_vertex_cap, size_t initial_index_cap) {
    FacetMesh* m = (FacetMesh*)calloc(1, sizeof(FacetMesh));
    if (!m) return NULL;

    m->vertex_capacity = initial_vertex_cap > 0 ? initial_vertex_cap : 64;
    m->vertices = (FacetVec3*)malloc(m->vertex_capacity * sizeof(FacetVec3));

    m->index_capacity = initial_index_cap > 0 ? initial_index_cap : 128;
    m->indices = (uint32_t*)malloc(m->index_capacity * sizeof(uint32_t));

    return m;
}

void facet_mesh_free(FacetMesh* mesh) {
    if (!mesh) return;
    free(mesh->vertices);
    free(mesh->indices);
    free(mesh->normals);
    free(mesh);
}

FacetMesh* facet_mesh_copy(const FacetMesh* src) {
    if (!src) return NULL;
    FacetMesh* dst = facet_mesh_create(src->vertex_count, src->index_count);
    if (!dst) return NULL;

    memcpy(dst->vertices, src->vertices, src->vertex_count * sizeof(FacetVec3));
    dst->vertex_count = src->vertex_count;

    memcpy(dst->indices, src->indices, src->index_count * sizeof(uint32_t));
    dst->index_count = src->index_count;

    if (src->normals && src->normal_count > 0) {
        dst->normals = (FacetVec3*)malloc(src->normal_count * sizeof(FacetVec3));
        memcpy(dst->normals, src->normals, src->normal_count * sizeof(FacetVec3));
        dst->normal_count = src->normal_count;
    }

    return dst;
}

uint32_t facet_mesh_add_vertex(FacetMesh* mesh, FacetVec3 v) {
    if (mesh->vertex_count >= mesh->vertex_capacity) {
        mesh->vertex_capacity *= 2;
        mesh->vertices = (FacetVec3*)realloc(mesh->vertices, mesh->vertex_capacity * sizeof(FacetVec3));
    }
    uint32_t idx = (uint32_t)mesh->vertex_count++;
    mesh->vertices[idx] = v;
    return idx;
}

void facet_mesh_add_triangle(FacetMesh* mesh, uint32_t i0, uint32_t i1, uint32_t i2) {
    if (mesh->index_count + 3 > mesh->index_capacity) {
        mesh->index_capacity = (mesh->index_capacity + 3) * 2;
        mesh->indices = (uint32_t*)realloc(mesh->indices, mesh->index_capacity * sizeof(uint32_t));
    }
    mesh->indices[mesh->index_count++] = i0;
    mesh->indices[mesh->index_count++] = i1;
    mesh->indices[mesh->index_count++] = i2;
}

void facet_mesh_compute_normals(FacetMesh* mesh) {
    if (!mesh || mesh->vertex_count == 0) return;

    free(mesh->normals);
    mesh->normals = (FacetVec3*)calloc(mesh->vertex_count, sizeof(FacetVec3));
    mesh->normal_count = mesh->vertex_count;

    for (size_t i = 0; i < mesh->index_count; i += 3) {
        uint32_t i0 = mesh->indices[i];
        uint32_t i1 = mesh->indices[i + 1];
        uint32_t i2 = mesh->indices[i + 2];

        FacetVec3 v0 = mesh->vertices[i0];
        FacetVec3 v1 = mesh->vertices[i1];
        FacetVec3 v2 = mesh->vertices[i2];

        FacetVec3 fn = facet_vec3_cross(facet_vec3_sub(v1, v0), facet_vec3_sub(v2, v0));
        mesh->normals[i0] = facet_vec3_add(mesh->normals[i0], fn);
        mesh->normals[i1] = facet_vec3_add(mesh->normals[i1], fn);
        mesh->normals[i2] = facet_vec3_add(mesh->normals[i2], fn);
    }

    for (size_t i = 0; i < mesh->vertex_count; ++i) {
        mesh->normals[i] = facet_vec3_normalize(mesh->normals[i]);
    }
}

FacetAABB facet_mesh_compute_aabb(const FacetMesh* mesh) {
    FacetAABB aabb;
    if (!mesh || mesh->vertex_count == 0) {
        aabb.min_pt = facet_vec3_create(0, 0, 0);
        aabb.max_pt = facet_vec3_create(0, 0, 0);
        return aabb;
    }

    aabb.min_pt = mesh->vertices[0];
    aabb.max_pt = mesh->vertices[0];

    for (size_t i = 1; i < mesh->vertex_count; ++i) {
        FacetVec3 v = mesh->vertices[i];
        if (v.x < aabb.min_pt.x) aabb.min_pt.x = v.x;
        if (v.y < aabb.min_pt.y) aabb.min_pt.y = v.y;
        if (v.z < aabb.min_pt.z) aabb.min_pt.z = v.z;

        if (v.x > aabb.max_pt.x) aabb.max_pt.x = v.x;
        if (v.y > aabb.max_pt.y) aabb.max_pt.y = v.y;
        if (v.z > aabb.max_pt.z) aabb.max_pt.z = v.z;
    }

    return aabb;
}

void facet_mesh_weld_vertices(FacetMesh* mesh, double tolerance) {
    if (!mesh || mesh->vertex_count == 0) return;

    uint32_t* remap = (uint32_t*)malloc(mesh->vertex_count * sizeof(uint32_t));
    FacetVec3* unique_v = (FacetVec3*)malloc(mesh->vertex_count * sizeof(FacetVec3));
    size_t unique_count = 0;

    for (size_t i = 0; i < mesh->vertex_count; ++i) {
        FacetVec3 v = mesh->vertices[i];
        int found_idx = -1;

        for (size_t u = 0; u < unique_count; ++u) {
            if (facet_vec3_approx_eq(v, unique_v[u], tolerance)) {
                found_idx = (int)u;
                break;
            }
        }

        if (found_idx >= 0) {
            remap[i] = (uint32_t)found_idx;
        } else {
            unique_v[unique_count] = v;
            remap[i] = (uint32_t)unique_count;
            unique_count++;
        }
    }

    for (size_t i = 0; i < mesh->index_count; ++i) {
        mesh->indices[i] = remap[mesh->indices[i]];
    }

    free(mesh->vertices);
    mesh->vertices = unique_v;
    mesh->vertex_count = unique_count;
    mesh->vertex_capacity = unique_count;

    free(remap);
}

bool facet_mesh_validate_manifold(const FacetMesh* mesh, int32_t* out_euler_char) {
    if (!mesh || mesh->vertex_count < 4 || mesh->index_count < 12) {
        if (out_euler_char) *out_euler_char = 0;
        return false;
    }

    // Number of faces is index_count / 3
    int32_t f = (int32_t)(mesh->index_count / 3);
    int32_t v = (int32_t)mesh->vertex_count;

    // For a triangulated closed 2-manifold without boundary: 3*F = 2*E => E = 3*F/2
    int32_t e = (3 * f) / 2;

    int32_t chi = v - e + f;
    if (out_euler_char) {
        *out_euler_char = chi;
    }

    return (chi == 2);
}
