# Facet

Facet is a verified 3D constructive solid geometry and boundary-representation modeling engine. It combines an exact, mechanically checked mathematical core in Agda with a high-throughput ISO C11 fastpath engine and terminal 3D visualization tools.

## Architecture

- Core Layer (Agda): Exact rational arithmetic, 3D vector space operations, orientation determinants, half-edge mesh topology invariants, Euler-Poincare characteristic preservation (V - E + F = 2), and binary space partitioning trees.
- Fastpath Layer (C11): AABB bounding volume hierarchies, polygon clipping, mesh welding, and binary STL and Wavefront OBJ streaming.
- Tools Layer (Python): Interactive 3D ASCII terminal wireframe visualizer, procedural CAD part generator, and regression testing suite.

## Building and Verification

Prerequisites:
- Agda 2.8+ with standard library
- C11 compliant compiler (Clang or GCC)
- Python 3.10+ (standard library only)

Run the full verification and build suite:

```bash
make all
```

Run demo CAD models and terminal visualization:

```bash
make demo
```

Run benchmarks and cross-language equivalence checks:

```bash
make benchmark
```
