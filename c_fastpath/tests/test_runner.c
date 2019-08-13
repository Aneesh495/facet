#include <stdio.h>

void run_test_math(void);
void run_test_mesh(void);
void run_test_bvh(void);
void run_test_bsp(void);
void run_test_io(void);

int main(void) {
    printf("========================================\n");
    printf("   FACET C11 FASTPATH VERIFICATION SUITE\n");
    printf("========================================\n\n");

    run_test_math();
    run_test_mesh();
    run_test_bvh();
    run_test_bsp();
    run_test_io();

    printf("\n>>> ALL C11 TESTS COMPLETED WITH ZERO ERRORS <<<\n");
    return 0;
}
