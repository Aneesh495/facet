#ifndef FACET_BSP_H
#define FACET_BSP_H

#include "facet_types.h"

typedef struct FacetBSPNode {
    FacetPlane partition;
    FacetTriangle* triangles;
    size_t triangle_count;
    size_t triangle_capacity;

    struct FacetBSPNode* front;
    struct FacetBSPNode* back;
} FacetBSPNode;

FacetBSPNode* facet_bsp_create_empty(void);
FacetBSPNode* facet_bsp_from_mesh(const FacetMesh* mesh);
void facet_bsp_free(FacetBSPNode* node);
void facet_bsp_invert(FacetBSPNode* node);

void facet_bsp_clip_triangles_to(FacetBSPNode* bsp, FacetMesh* in_out_mesh);
FacetMesh* facet_bsp_boolean(const FacetMesh* mesh_a, const FacetMesh* mesh_b, FacetCSGOp op);

#endif // FACET_BSP_H
