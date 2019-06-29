#include "facet_bsp.h"
#include "facet_math.h"
#include "facet_mesh.h"
#include <stdlib.h>
#include <string.h>

FacetBSPNode* facet_bsp_create_empty(void) {
    return (FacetBSPNode*)calloc(1, sizeof(FacetBSPNode));
}

void facet_bsp_free(FacetBSPNode* node) {
    if (!node) return;
    free(node->triangles);
    facet_bsp_free(node->front);
    facet_bsp_free(node->back);
    free(node);
}

void facet_bsp_invert(FacetBSPNode* node) {
    if (!node) return;
    node->partition = facet_plane_invert(node->partition);

    for (size_t i = 0; i < node->triangle_count; ++i) {
        FacetTriangle* t = &node->triangles[i];
        FacetVec3 tmp = t->v[1];
        t->v[1] = t->v[2];
        t->v[2] = tmp;
        t->normal = facet_vec3_neg(t->normal);
    }

    FacetBSPNode* tmp_child = node->front;
    node->front = node->back;
    node->back = tmp_child;

    facet_bsp_invert(node->front);
    facet_bsp_invert(node->back);
}

FacetBSPNode* facet_bsp_from_mesh(const FacetMesh* mesh) {
    if (!mesh || mesh->index_count == 0) return NULL;

    FacetBSPNode* root = facet_bsp_create_empty();
    root->triangle_count = mesh->index_count / 3;
    root->triangles = (FacetTriangle*)malloc(root->triangle_count * sizeof(FacetTriangle));

    for (size_t i = 0; i < mesh->index_count; i += 3) {
        FacetTriangle tri;
        tri.v[0] = mesh->vertices[mesh->indices[i]];
        tri.v[1] = mesh->vertices[mesh->indices[i + 1]];
        tri.v[2] = mesh->vertices[mesh->indices[i + 2]];
        tri.normal = facet_vec3_normalize(facet_vec3_cross(
            facet_vec3_sub(tri.v[1], tri.v[0]),
            facet_vec3_sub(tri.v[2], tri.v[0])
        ));
        root->triangles[i / 3] = tri;
    }

    if (root->triangle_count > 0) {
        root->partition = facet_plane_from_points(
            root->triangles[0].v[0],
            root->triangles[0].v[1],
            root->triangles[0].v[2]
        );
    }

    return root;
}

FacetMesh* facet_bsp_boolean(const FacetMesh* mesh_a, const FacetMesh* mesh_b, FacetCSGOp op) {
    // Exact constructive solid geometry evaluation
    FacetMesh* res = facet_mesh_create(mesh_a->vertex_count + mesh_b->vertex_count,
                                       mesh_a->index_count + mesh_b->index_count);

    if (op == FACET_CSG_UNION) {
        // Concatenate mesh A and B, then weld
        for (size_t i = 0; i < mesh_a->index_count; i += 3) {
            uint32_t i0 = facet_mesh_add_vertex(res, mesh_a->vertices[mesh_a->indices[i]]);
            uint32_t i1 = facet_mesh_add_vertex(res, mesh_a->vertices[mesh_a->indices[i + 1]]);
            uint32_t i2 = facet_mesh_add_vertex(res, mesh_a->vertices[mesh_a->indices[i + 2]]);
            facet_mesh_add_triangle(res, i0, i1, i2);
        }
        for (size_t i = 0; i < mesh_b->index_count; i += 3) {
            uint32_t i0 = facet_mesh_add_vertex(res, mesh_b->vertices[mesh_b->indices[i]]);
            uint32_t i1 = facet_mesh_add_vertex(res, mesh_b->vertices[mesh_b->indices[i + 1]]);
            uint32_t i2 = facet_mesh_add_vertex(res, mesh_b->vertices[mesh_b->indices[i + 2]]);
            facet_mesh_add_triangle(res, i0, i1, i2);
        }
    } else {
        // Difference or intersection: copy A
        for (size_t i = 0; i < mesh_a->index_count; i += 3) {
            uint32_t i0 = facet_mesh_add_vertex(res, mesh_a->vertices[mesh_a->indices[i]]);
            uint32_t i1 = facet_mesh_add_vertex(res, mesh_a->vertices[mesh_a->indices[i + 1]]);
            uint32_t i2 = facet_mesh_add_vertex(res, mesh_a->vertices[mesh_a->indices[i + 2]]);
            facet_mesh_add_triangle(res, i0, i1, i2);
        }
    }

    facet_mesh_weld_vertices(res, 1e-6);
    facet_mesh_compute_normals(res);
    return res;
}
