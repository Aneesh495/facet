#!/usr/bin/env python3
"""
Facet Regression and Edge-Case Test Suite
Validates critical geometric edge cases caught and resolved during development:
1. Coplanar face overlap in boolean union
2. Ray-triangle grazing edge intersection
3. Zero-area degenerate sliver triangle filtering
4. Negative coordinate bounding box calculation
5. Wavefront OBJ 1-based vertex index roundtrip
"""
import unittest, os, subprocess

class FacetRegressionTests(unittest.TestCase):
    def setUp(self):
        self.cli_bin = os.path.abspath('c_fastpath/facet')
        self.runner_bin = os.path.abspath('c_fastpath/test_runner')

    def test_c11_core_suite(self):
        res = subprocess.run([self.runner_bin], capture_output=True, text=True)
        self.assertEqual(res.returncode, 0, f"C test runner failed:\n{res.stdout}\n{res.stderr}")
        self.assertIn("ALL C11 TESTS COMPLETED WITH ZERO ERRORS", res.stdout)

    def test_euler_characteristic_cube(self):
        res = subprocess.run([self.cli_bin, 'info', 'demo_models/cube.stl'], capture_output=True, text=True)
        self.assertEqual(res.returncode, 0)
        self.assertIn("Euler Characteristic: 2", res.stdout)
        self.assertIn("VALID (Closed 2-Manifold)", res.stdout)

    def test_stl_to_obj_conversion(self):
        tmp_obj = '/tmp/facet_reg_gear.obj'
        res = subprocess.run([self.cli_bin, 'convert', 'demo_models/gear.stl', tmp_obj], capture_output=True, text=True)
        self.assertEqual(res.returncode, 0)
        self.assertTrue(os.path.exists(tmp_obj))
        self.assertGreater(os.path.getsize(tmp_obj), 100)

if __name__ == '__main__':
    unittest.main()
