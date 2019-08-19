#!/usr/bin/env python3
"""
Facet Terminal 3D ASCII Mesh Visualizer
Renders shaded wireframes and depth-buffered projections of STL models directly in terminal.
"""
import sys, math, struct

def read_stl_triangles(filepath):
    triangles = []
    with open(filepath, 'rb') as f:
        header = f.read(80)
        num_tri_bytes = f.read(4)
        if len(num_tri_bytes) < 4:
            return triangles
        num_triangles = struct.unpack('<I', num_tri_bytes)[0]
        for _ in range(num_triangles):
            data = f.read(50)
            if len(data) < 50:
                break
            floats = struct.unpack('<12fH', data)
            normal = (floats[0], floats[1], floats[2])
            v0 = (floats[3], floats[4], floats[5])
            v1 = (floats[6], floats[7], floats[8])
            v2 = (floats[9], floats[10], floats[11])
            triangles.append((normal, v0, v1, v2))
    return triangles

def render_ascii(triangles, width=80, height=36, yaw=0.6, pitch=0.4):
    if not triangles:
        print("Empty or invalid mesh.")
        return

    # Compute bounding box
    all_pts = [v for tri in triangles for v in (tri[1], tri[2], tri[3])]
    min_x = min(p[0] for p in all_pts)
    max_x = max(p[0] for p in all_pts)
    min_y = min(p[1] for p in all_pts)
    max_y = max(p[1] for p in all_pts)
    min_z = min(p[2] for p in all_pts)
    max_z = max(p[2] for p in all_pts)

    cx = (min_x + max_x) * 0.5
    cy = (min_y + max_y) * 0.5
    cz = (min_z + max_z) * 0.5
    extent = max(max_x - min_x, max_y - min_y, max_z - min_z)
    if extent == 0:
        extent = 1.0

    scale = min(width * 0.45, height * 0.9) / extent

    # Rotate point
    cos_y, sin_y = math.cos(yaw), math.sin(yaw)
    cos_p, sin_p = math.cos(pitch), math.sin(pitch)

    def project(pt):
        x = pt[0] - cx
        y = pt[1] - cy
        z = pt[2] - cz

        # Yaw around Y
        x1 = x * cos_y + z * sin_y
        y1 = y
        z1 = -x * sin_y + z * cos_y

        # Pitch around X
        x2 = x1
        y2 = y1 * cos_p - z1 * sin_p
        z2 = y1 * sin_p + z1 * cos_p

        screen_x = int(width * 0.5 + x2 * scale * 1.8)
        screen_y = int(height * 0.5 - y2 * scale)
        return screen_x, screen_y, z2

    zbuffer = [[-1e9 for _ in range(width)] for _ in range(height)]
    frame = [[' ' for _ in range(width)] for _ in range(height)]
    shading_chars = " .:-=+*#%@"

    light_dir = (0.577, 0.577, 0.577)

    for normal, v0, v1, v2 in triangles:
        p0 = project(v0)
        p1 = project(v1)
        p2 = project(v2)

        # Flat shading based on light dot product
        nl = normal[0]*light_dir[0] + normal[1]*light_dir[1] + normal[2]*light_dir[2]
        intensity = max(0.0, min(1.0, nl * 0.7 + 0.3))
        char_idx = int(intensity * (len(shading_chars) - 1))
        char = shading_chars[char_idx]

        # Draw wireframe edges
        def draw_line(pA, pB):
            x0, y0, z0 = pA
            x1, y1, z1 = pB
            dx = abs(x1 - x0)
            dy = abs(y1 - y0)
            steps = max(dx, dy, 1)
            for s in range(steps + 1):
                t = s / steps
                px = int(x0 + (x1 - x0) * t)
                py = int(y0 + (y1 - y0) * t)
                pz = z0 + (z1 - z0) * t
                if 0 <= px < width and 0 <= py < height:
                    if pz > zbuffer[py][px]:
                        zbuffer[py][px] = pz
                        frame[py][px] = char

        draw_line(p0, p1)
        draw_line(p1, p2)
        draw_line(p2, p0)

    print("+" + "-" * width + "+")
    for row in frame:
        print("|" + "".join(row) + "|")
    print("+" + "-" * width + "+")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: ascii_viewer.py <mesh.stl>")
        sys.exit(1)
    tris = read_stl_triangles(sys.argv[1])
    print(f"Loaded {len(tris)} facets from {sys.argv[1]}")
    render_ascii(tris)
