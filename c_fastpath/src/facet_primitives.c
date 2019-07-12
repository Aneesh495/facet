#include <stdlib.h>
#include "facet_primitives.h"
#include "facet_mesh.h"
#include "facet_math.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

FacetMesh* facet_primitive_cube(double size_x, double size_y, double size_z) {
    FacetMesh* m = facet_mesh_create(8, 36);
    double hx = size_x * 0.5, hy = size_y * 0.5, hz = size_z * 0.5;

    // 8 vertices
    uint32_t v0 = facet_mesh_add_vertex(m, facet_vec3_create(-hx, -hy, -hz));
    uint32_t v1 = facet_mesh_add_vertex(m, facet_vec3_create( hx, -hy, -hz));
    uint32_t v2 = facet_mesh_add_vertex(m, facet_vec3_create( hx,  hy, -hz));
    uint32_t v3 = facet_mesh_add_vertex(m, facet_vec3_create(-hx,  hy, -hz));
    uint32_t v4 = facet_mesh_add_vertex(m, facet_vec3_create(-hx, -hy,  hz));
    uint32_t v5 = facet_mesh_add_vertex(m, facet_vec3_create( hx, -hy,  hz));
    uint32_t v6 = facet_mesh_add_vertex(m, facet_vec3_create( hx,  hy,  hz));
    uint32_t v7 = facet_mesh_add_vertex(m, facet_vec3_create(-hx,  hy,  hz));

    // 6 quad faces -> 12 triangles
    // Front face (Z+)
    facet_mesh_add_triangle(m, v4, v5, v6);
    facet_mesh_add_triangle(m, v4, v6, v7);
    // Back face (Z-)
    facet_mesh_add_triangle(m, v1, v0, v3);
    facet_mesh_add_triangle(m, v1, v3, v2);
    // Left face (X-)
    facet_mesh_add_triangle(m, v0, v4, v7);
    facet_mesh_add_triangle(m, v0, v7, v3);
    // Right face (X+)
    facet_mesh_add_triangle(m, v5, v1, v2);
    facet_mesh_add_triangle(m, v5, v2, v6);
    // Top face (Y+)
    facet_mesh_add_triangle(m, v7, v6, v2);
    facet_mesh_add_triangle(m, v7, v2, v3);
    // Bottom face (Y-)
    facet_mesh_add_triangle(m, v0, v1, v5);
    facet_mesh_add_triangle(m, v0, v5, v4);

    facet_mesh_compute_normals(m);
    return m;
}

FacetMesh* facet_primitive_cylinder(double radius, double height, uint32_t segments) {
    if (segments < 3) segments = 3;
    FacetMesh* m = facet_mesh_create(segments * 2 + 2, segments * 12);
    double hh = height * 0.5;

    uint32_t bot_center = facet_mesh_add_vertex(m, facet_vec3_create(0, -hh, 0));
    uint32_t top_center = facet_mesh_add_vertex(m, facet_vec3_create(0,  hh, 0));

    uint32_t* bot_ring = (uint32_t*)malloc(segments * sizeof(uint32_t));
    uint32_t* top_ring = (uint32_t*)malloc(segments * sizeof(uint32_t));

    for (uint32_t i = 0; i < segments; ++i) {
        double theta = (2.0 * M_PI * (double)i) / (double)segments;
        double x = radius * cos(theta);
        double z = radius * sin(theta);
        bot_ring[i] = facet_mesh_add_vertex(m, facet_vec3_create(x, -hh, z));
        top_ring[i] = facet_mesh_add_vertex(m, facet_vec3_create(x,  hh, z));
    }

    for (uint32_t i = 0; i < segments; ++i) {
        uint32_t next = (i + 1) % segments;
        // Bottom cap
        facet_mesh_add_triangle(m, bot_center, bot_ring[next], bot_ring[i]);
        // Top cap
        facet_mesh_add_triangle(m, top_center, top_ring[i], top_ring[next]);
        // Side quad
        facet_mesh_add_triangle(m, bot_ring[i], bot_ring[next], top_ring[next]);
        facet_mesh_add_triangle(m, bot_ring[i], top_ring[next], top_ring[i]);
    }

    free(bot_ring);
    free(top_ring);
    facet_mesh_compute_normals(m);
    return m;
}

FacetMesh* facet_primitive_sphere(double radius, uint32_t rings, uint32_t sectors) {
    if (rings < 2) rings = 2;
    if (sectors < 3) sectors = 3;

    FacetMesh* m = facet_mesh_create(rings * sectors, rings * sectors * 6);

    for (uint32_t r = 0; r <= rings; ++r) {
        double phi = M_PI * (double)r / (double)rings;
        double y = radius * cos(phi);
        double r_sin = radius * sin(phi);

        for (uint32_t s = 0; s <= sectors; ++s) {
            double theta = 2.0 * M_PI * (double)s / (double)sectors;
            double x = r_sin * cos(theta);
            double z = r_sin * sin(theta);
            facet_mesh_add_vertex(m, facet_vec3_create(x, y, z));
        }
    }

    for (uint32_t r = 0; r < rings; ++r) {
        for (uint32_t s = 0; s < sectors; ++s) {
            uint32_t cur = r * (sectors + 1) + s;
            uint32_t next = cur + (sectors + 1);

            facet_mesh_add_triangle(m, cur, next, cur + 1);
            facet_mesh_add_triangle(m, cur + 1, next, next + 1);
        }
    }

    facet_mesh_weld_vertices(m, 1e-6);
    facet_mesh_compute_normals(m);
    return m;
}

FacetMesh* facet_primitive_gear(
    double pitch_radius, double thickness, uint32_t teeth,
    double bore_radius, double keyway_width
) {
    (void)bore_radius;
    (void)keyway_width;
    uint32_t segments = teeth * 4;
    return facet_primitive_cylinder(pitch_radius, thickness, segments);
}
