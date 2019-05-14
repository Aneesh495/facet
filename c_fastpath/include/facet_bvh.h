#ifndef FACET_BVH_H
#define FACET_BVH_H

#include "facet_types.h"

typedef struct FacetBVHNode {
    FacetAABB bounds;
    int32_t left_child;
    int32_t right_child;
    uint32_t triangle_offset;
    uint32_t triangle_count;
} FacetBVHNode;

typedef struct {
    FacetBVHNode* nodes;
    size_t node_count;
    size_t node_capacity;

    uint32_t* triangle_indices;
    size_t triangle_count;
} FacetBVH;

FacetBVH* facet_bvh_create(const FacetMesh* mesh);
void facet_bvh_free(FacetBVH* bvh);
bool facet_bvh_ray_query(
    const FacetBVH* bvh, const FacetMesh* mesh,
    FacetVec3 ray_orig, FacetVec3 ray_dir,
    double* out_hit_t, uint32_t* out_triangle_idx
);

#endif // FACET_BVH_H
