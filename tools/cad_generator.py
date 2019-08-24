#!/usr/bin/env python3
"""
Procedural Mechanical CAD Generator
Generates complex benchmark geometries and validation parts.
"""
import sys, os, subprocess

def generate_benchmark_parts(out_dir):
    os.makedirs(out_dir, exist_ok=True)
    cli_bin = os.path.join(os.path.dirname(__file__), '..', 'c_fastpath', 'facet')

    if not os.path.isfile(cli_bin):
        print(f"Error: {cli_bin} not built. Run make first.")
        return False

    print("Generating procedural CAD parts...")
    res = subprocess.run([cli_bin, 'demo', out_dir], capture_output=True, text=True)
    print(res.stdout)
    return res.returncode == 0

if __name__ == '__main__':
    target = sys.argv[1] if len(sys.argv) > 1 else 'demo_models'
    generate_benchmark_parts(target)
