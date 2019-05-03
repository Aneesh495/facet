#ifndef FACET_TYPES_H
#define FACET_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// 3D vector with double precision components
typedef struct {
    double x;
    double y;
    double z;
} FacetVec3;

// 3x3 row-major transformation matrix
typedef struct {
    FacetVec3 row[3];
} FacetMat3;

// Spatial plane equation: normal . p - dist = 0
typedef struct {
    FacetVec3 normal;
    double dist;
} FacetPlane;

// Axis-aligned bounding box
typedef struct {
    FacetVec3 min_pt;
    FacetVec3 max_pt;
} FacetAABB;

// 3D triangle defined by 3 vertices and facet normal
typedef struct {
    FacetVec3 v[3];
    FacetVec3 normal;
} FacetTriangle;

// Dynamic triangle mesh representation
typedef struct {
    FacetVec3* vertices;
    size_t vertex_count;
    size_t vertex_capacity;

    uint32_t* indices;
    size_t index_count;
    size_t index_capacity;

    FacetVec3* normals;
    size_t normal_count;
} FacetMesh;

// CSG Boolean operation types
typedef enum {
    FACET_CSG_UNION,
    FACET_CSG_INTERSECT,
    FACET_CSG_DIFFERENCE
} FacetCSGOp;

// Spatial side classification
typedef enum {
    FACET_SIDE_COPLANAR = 0,
    FACET_SIDE_FRONT    = 1,
    FACET_SIDE_BACK     = 2,
    FACET_SIDE_SPANNING = 3
} FacetSpatialSide;

#endif // FACET_TYPES_H
