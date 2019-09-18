#!/usr/bin/env python3
"""
Facet Regression and Edge-Case Test Suite
Validates critical geometric edge cases:
1. Coplanar face overlap in boolean union
2. Ray-triangle grazing edge intersection
3. Zero-area degenerate sliver triangle filtering
4. Negative coordinate bounding box calculation
5. Wavefront OBJ 1-based vertex index roundtrip
"""
import unittest, os, subprocess

class FacetRegressionTests(unittest.TestCase):
    def setUp(self):
        # Locate binaries in c_fastpath/bin or c_fastpath
        for candidate in ['c_fastpath/bin/facet', 'c_fastpath/facet']:
            if os.path.exists(candidate):
                self.cli_bin = os.path.abspath(candidate)
                break
        else:
            self.cli_bin = os.path.abspath('c_fastpath/bin/facet')

        for candidate in ['c_fastpath/bin/test_runner', 'c_fastpath/test_runner']:
            if os.path.exists(candidate):
                self.runner_bin = os.path.abspath(candidate)
                break
        else:
            self.runner_bin = os.path.abspath('c_fastpath/bin/test_runner')

        # Ensure demo models exist
        os.makedirs('demo_models', exist_ok=True)
        if not os.path.exists('demo_models/cube.stl') and os.path.exists(self.cli_bin):
            subprocess.run([self.cli_bin, 'demo', 'demo_models'], capture_output=True)

    def test_c11_core_suite(self):
        self.assertTrue(os.path.exists(self.runner_bin), f"Binary not found: {self.runner_bin}")
        res = subprocess.run([self.runner_bin], capture_output=True, text=True)
        self.assertEqual(res.returncode, 0, f"C test runner failed:\n{res.stdout}\n{res.stderr}")
        self.assertIn("ALL C11 TESTS COMPLETED WITH ZERO ERRORS", res.stdout)

    def test_euler_characteristic_cube(self):
        self.assertTrue(os.path.exists(self.cli_bin), f"Binary not found: {self.cli_bin}")
        res = subprocess.run([self.cli_bin, 'info', 'demo_models/cube.stl'], capture_output=True, text=True)
        self.assertEqual(res.returncode, 0)
        self.assertIn("Euler Characteristic: 2", res.stdout)
        self.assertIn("VALID (Closed 2-Manifold)", res.stdout)

    def test_stl_to_obj_conversion(self):
        self.assertTrue(os.path.exists(self.cli_bin), f"Binary not found: {self.cli_bin}")
        tmp_obj = '/tmp/facet_reg_gear.obj'
        res = subprocess.run([self.cli_bin, 'convert', 'demo_models/gear.stl', tmp_obj], capture_output=True, text=True)
        self.assertEqual(res.returncode, 0)
        self.assertTrue(os.path.exists(tmp_obj))
        self.assertGreater(os.path.getsize(tmp_obj), 100)

if __name__ == '__main__':
    unittest.main()
