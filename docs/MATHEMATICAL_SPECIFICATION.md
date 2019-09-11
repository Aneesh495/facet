# Facet Mathematical Specification

## Exact Rational Coordinates

All foundational spatial vertices are represented using exact rational coordinates:

$$q = \frac{n}{d}, \quad n \in \mathbb{Z}, \; d \in \mathbb{N}^+$$

This prevents rounding errors, inverted surface normals, and degenerate zero-area triangles common to floating-point geometry kernels.

## Exact Spatial Orientation Predicate (Orient3D)

For four 3D spatial points $a, b, c, d \in \mathbb{Q}^3$, the orientation determinant is defined by the signed 4x4 matrix:

$$\text{Orient3D}(a, b, c, d) = \det \begin{pmatrix} a_x & a_y & a_z & 1 \\ b_x & b_y & b_z & 1 \\ c_x & c_y & c_z & 1 \\ d_x & d_y & d_z & 1 \end{pmatrix}$$

Expanding along minors relative to vertex $a$:

$$\text{Orient3D}(a, b, c, d) = (b - a) \cdot ((c - a) \times (d - a))$$

- $\text{Orient3D} > 0$: Point $d$ lies below the oriented plane through $a, b, c$.
- $\text{Orient3D} < 0$: Point $d$ lies above the plane.
- $\text{Orient3D} = 0$: The four points are coplanar.

## Euler-Poincare Characteristic

For any closed polyhedral 2-manifold without boundary:

$$\chi = V - E + F = 2(1 - g)$$

For genus $g = 0$ (spherical topology), $\chi = 2$.
