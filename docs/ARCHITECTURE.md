# Facet Architecture Specification

## Overview

Facet is a verified 3D constructive solid geometry (CSG) and boundary-representation (B-Rep) modeling engine. It pairs a formally verified mathematical core in Agda with a high-throughput ISO C11 fastpath engine and Python visualization tooling.

```mermaid
flowchart TD
    subgraph Core [Agda Verified Core]
        Exact[Exact Rational Coordinates] --> Predicates[Exact Orientation Predicates]
        Predicates --> HalfEdge[Half-Edge Topology]
        HalfEdge --> Euler[Euler-Poincare Verification]
        Euler --> BSPTree[Binary Space Partitioning]
        BSPTree --> CSGBoolean[CSG Boolean Algebra]
    end

    subgraph Fastpath [ISO C11 Fastpath Engine]
        BVH[Surface Area Heuristic BVH] --> RayIntersect[SIMD Ray-Triangle Intersect]
        FastBSP[In-Place Triangle Slicing] --> MeshWeld[Spatial Hash Vertex Welding]
        MeshWeld --> StreamingIO[Binary STL and OBJ IO]
    end

    subgraph Tooling [Python Clinical and Dev Tooling]
        ASCIIViewer[Terminal 3D ASCII Visualizer]
        CADGen[Procedural Mechanical Synthesizer]
        Equivalence[Cross-Language Equivalence Checker]
        Regression[Edge-Case Regression Suite]
    end

    Core --> Fastpath
    Fastpath --> Tooling
```

## Topological Invariants

Facet enforces the following constructive properties:
1. Every directed half-edge has a unique inverse twin.
2. Every face cycle is strictly closed.
3. The boundary operator is nilpotent: the boundary of a boundary is empty.
4. Euler-Poincare characteristic preservation: V - E + F = 2 for closed genus-0 2-manifolds.
