#ifndef FACET_MESH_H
#define FACET_MESH_H

#include "facet_types.h"

FacetMesh* facet_mesh_create(size_t initial_vertex_cap, size_t initial_index_cap);
void facet_mesh_free(FacetMesh* mesh);
FacetMesh* facet_mesh_copy(const FacetMesh* src);

uint32_t facet_mesh_add_vertex(FacetMesh* mesh, FacetVec3 v);
void facet_mesh_add_triangle(FacetMesh* mesh, uint32_t i0, uint32_t i1, uint32_t i2);
void facet_mesh_compute_normals(FacetMesh* mesh);
void facet_mesh_weld_vertices(FacetMesh* mesh, double tolerance);
FacetAABB facet_mesh_compute_aabb(const FacetMesh* mesh);

bool facet_mesh_validate_manifold(const FacetMesh* mesh, int32_t* out_euler_char);

#endif // FACET_MESH_H
