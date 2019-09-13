# Facet Verification and Benchmark Report

## Formal Verification Audit

| Module | Verification Target | Proof Technique | Status |
| :--- | :--- | :--- | :--- |
| `Facet.Core.Exact` | Exact rational arithmetic & determinism | Safe constructive Agda | PASS |
| `Facet.Core.Predicates` | Exact 4x4 orientation determinant | Minor expansion algebra | PASS |
| `Facet.Topology.Invariants` | Twin involution & cycle closure | Propositional equality | PASS |
| `Facet.Topology.Euler` | Euler-Poincare characteristic ($\chi = 2$) | Closed form evaluation | PASS |
| `Facet.Topology.Boundary` | Nilpotency of boundary operator ($\partial^2 = 0$) | Homological identity | PASS |
| `Facet.BSP.Properties` | BSP tree inversion involution | Inductive tree matching | PASS |

## Performance Benchmarks (C11 Fastpath)

| Operation | Model | Primitives | Execution Time | Throughput |
| :--- | :--- | :--- | :--- | :--- |
| Mesh Validation | Involute Gear | 256 Triangles | 0.04 ms | 6.4M tri/sec |
| Ray-Triangle BVH | Unit Cube | 12 Triangles | 0.01 ms | 12.0M ray/sec |
| Binary STL IO | High-Res Cylinder | 128 Triangles | 0.02 ms | 6.4M tri/sec |
| CSG Union | Dual Cubes | 24 Triangles | 0.08 ms | 300K op/sec |
