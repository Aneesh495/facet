# Facet Bug Audit Log and Regression Cases

Every bug identified during the engineering and testing of Facet was captured with a failing test case prior to resolution:

## BUG-001: Coplanar Face Overlap in CSG Boolean Union
- **Symptom**: Merging two identical abutting cubes resulted in duplicate internal coplanar polygons that violated 2-manifold edge sharing.
- **Root Cause**: The splitting plane classifier assigned coplanar polygons to both front and back trees without marking them as boundary-shared.
- **Resolution**: Implemented spatial hash vertex welding and coplanar polygon classification into `SpanCoplanar` partitions.
- **Regression Test**: `test_bsp.c:run_test_bsp()` and `tools/regression_suite.py:test_c11_core_suite()`.

## BUG-002: Ray-Triangle Grazing Edge False Misses
- **Symptom**: Rays grazing the exact boundary edge between two triangles occasionally returned false negatives.
- **Root Cause**: Strict `< 0.0` check on barycentric coordinates rejected edge-aligned hits due to machine epsilon.
- **Resolution**: Introduced adaptive tolerance thresholding `FACET_EPSILON` in `facet_math.c:facet_ray_triangle_intersect()`.
- **Regression Test**: `test_bvh.c:run_test_bvh()`.

## BUG-003: Wavefront OBJ 1-Based Vertex Indexing Mismatch
- **Symptom**: Converting binary STL to Wavefront OBJ caused vertex index off-by-one errors in third-party viewers.
- **Root Cause**: Wavefront OBJ format uses 1-based indexing, whereas internal arrays are 0-based.
- **Resolution**: Added explicit index incrementation in `facet_obj.c:facet_obj_write()`.
- **Regression Test**: `tools/regression_suite.py:test_stl_to_obj_conversion()`.
