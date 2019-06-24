#include "facet_bvh.h"
#include "facet_math.h"
#include <stdlib.h>
#include <float.h>

FacetBVH* facet_bvh_create(const FacetMesh* mesh) {
    if (!mesh || mesh->index_count == 0) return NULL;

    FacetBVH* bvh = (FacetBVH*)calloc(1, sizeof(FacetBVH));
    bvh->triangle_count = mesh->index_count / 3;
    bvh->triangle_indices = (uint32_t*)malloc(bvh->triangle_count * sizeof(uint32_t));

    for (uint32_t i = 0; i < (uint32_t)bvh->triangle_count; ++i) {
        bvh->triangle_indices[i] = i;
    }

    // Root node
    bvh->node_capacity = 2 * bvh->triangle_count + 1;
    bvh->nodes = (FacetBVHNode*)calloc(bvh->node_capacity, sizeof(FacetBVHNode));

    FacetBVHNode* root = &bvh->nodes[bvh->node_count++];
    root->left_child = -1;
    root->right_child = -1;
    root->triangle_offset = 0;
    root->triangle_count = (uint32_t)bvh->triangle_count;

    // Compute root bounds
    root->bounds.min_pt = facet_vec3_create(DBL_MAX, DBL_MAX, DBL_MAX);
    root->bounds.max_pt = facet_vec3_create(-DBL_MAX, -DBL_MAX, -DBL_MAX);

    for (size_t i = 0; i < mesh->vertex_count; ++i) {
        FacetVec3 pt = mesh->vertices[i];
        if (pt.x < root->bounds.min_pt.x) root->bounds.min_pt.x = pt.x;
        if (pt.y < root->bounds.min_pt.y) root->bounds.min_pt.y = pt.y;
        if (pt.z < root->bounds.min_pt.z) root->bounds.min_pt.z = pt.z;

        if (pt.x > root->bounds.max_pt.x) root->bounds.max_pt.x = pt.x;
        if (pt.y > root->bounds.max_pt.y) root->bounds.max_pt.y = pt.y;
        if (pt.z > root->bounds.max_pt.z) root->bounds.max_pt.z = pt.z;
    }

    return bvh;
}

void facet_bvh_free(FacetBVH* bvh) {
    if (!bvh) return;
    free(bvh->nodes);
    free(bvh->triangle_indices);
    free(bvh);
}

bool facet_bvh_ray_query(
    const FacetBVH* bvh, const FacetMesh* mesh,
    FacetVec3 ray_orig, FacetVec3 ray_dir,
    double* out_hit_t, uint32_t* out_triangle_idx
) {
    if (!bvh || !mesh) return false;

    double closest_t = DBL_MAX;
    uint32_t hit_tri = 0;
    bool hit_any = false;

    for (size_t i = 0; i < mesh->index_count; i += 3) {
        FacetVec3 v0 = mesh->vertices[mesh->indices[i]];
        FacetVec3 v1 = mesh->vertices[mesh->indices[i + 1]];
        FacetVec3 v2 = mesh->vertices[mesh->indices[i + 2]];

        double t, u, v;
        if (facet_ray_triangle_intersect(ray_orig, ray_dir, v0, v1, v2, &t, &u, &v)) {
            if (t < closest_t) {
                closest_t = t;
                hit_tri = (uint32_t)(i / 3);
                hit_any = true;
            }
        }
    }

    if (hit_any) {
        if (out_hit_t) *out_hit_t = closest_t;
        if (out_triangle_idx) *out_triangle_idx = hit_tri;
    }

    return hit_any;
}
