.PHONY: all agda-check c-build test benchmark clean help demo info

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -O3 -I c_fastpath/include
LDFLAGS = -lm

all: agda-check c-build test

agda-check:
	@echo "=== Checking Agda Formally Verified Core ==="
	agda -isrc src/Facet.agda
	agda -isrc -itests/agda tests/agda/TestAll.agda
	@echo "Agda Core Verified Successfully."

c-build:
	@echo "=== Building C11 Fastpath Engine ==="
	mkdir -p c_fastpath/bin
	$(CC) $(CFLAGS) 		c_fastpath/src/facet_math.c 		c_fastpath/src/facet_mesh.c 		c_fastpath/src/facet_bvh.c 		c_fastpath/src/facet_bsp.c 		c_fastpath/src/facet_stl.c 		c_fastpath/src/facet_obj.c 		c_fastpath/src/facet_primitives.c 		c_fastpath/src/facet_main.c 		$(LDFLAGS) -o c_fastpath/bin/facet
	$(CC) $(CFLAGS) 		c_fastpath/src/facet_math.c 		c_fastpath/src/facet_mesh.c 		c_fastpath/src/facet_bvh.c 		c_fastpath/src/facet_bsp.c 		c_fastpath/src/facet_stl.c 		c_fastpath/src/facet_obj.c 		c_fastpath/src/facet_primitives.c 		c_fastpath/tests/test_math.c 		c_fastpath/tests/test_mesh.c 		c_fastpath/tests/test_bvh.c 		c_fastpath/tests/test_bsp.c 		c_fastpath/tests/test_io.c 		c_fastpath/tests/test_runner.c 		$(LDFLAGS) -o c_fastpath/bin/test_runner
	@echo "C11 Fastpath Built Successfully."

test: c-build
	@echo "=== Running C11 Fastpath Test Suite ==="
	./c_fastpath/bin/test_runner
	@echo "=== Running Python Regression Suite ==="
	python3 tools/regression_suite.py
	python3 tools/equivalence_checker.py

demo: c-build
	@echo "=== Generating Demo CAD Models ==="
	mkdir -p demo_models
	./c_fastpath/bin/facet demo demo_models
	python3 tools/ascii_viewer.py demo_models/cube.stl

benchmark: c-build
	@echo "=== Running Performance Benchmarks ==="
	python3 tools/equivalence_checker.py

clean:
	rm -rf _build/ *.agdai c_fastpath/bin/ c_fastpath/test_runner c_fastpath/facet demo_models/ output/ /tmp/facet_*

help:
	@echo "Facet Build System Targets:"
	@echo "  make all         Verify Agda, compile C fastpath, run tests"
	@echo "  make agda-check  Verify Agda dependent-type proofs"
	@echo "  make c-build     Compile optimized C11 engine"
	@echo "  make test        Execute all unit and regression test suites"
	@echo "  make demo        Generate 3D solids and render in ASCII terminal"
	@echo "  make benchmark   Run equivalence and throughput benchmarks"
	@echo "  make clean       Remove all build artifacts and temporary files"
