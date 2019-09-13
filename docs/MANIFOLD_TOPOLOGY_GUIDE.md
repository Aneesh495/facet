# Facet Manifold Topology Guide

## The Half-Edge Data Structure

In boundary-representation modeling, polygon meshes are structured into directed half-edges:

```
          v1  <--------- h_twin ---------  v0
           |  -------- h_forward --------> |
           |                               |
           v                               ^
```

Each half-edge maintains:
- `origin`: Vertex index where the edge originates.
- `target`: Vertex index where the edge terminates.
- `twin`: Pointer to the oppositely directed sibling edge on the adjacent face.
- `next`: Pointer to the next edge along the face cycle.
- `prev`: Pointer to the preceding edge along the face cycle.
- `face`: Pointer to the incident planar polygon face.

## Boundary Closure Invariant

A mesh is a valid closed 2-manifold if and only if:
1. Every edge is shared by exactly two faces with opposite directions.
2. The neighbourhood of every vertex is homeomorphic to an open 2D disk.
3. No self-intersections exist among face interiors.
