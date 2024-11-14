#include "util.h"

unsigned int N, M, w, x, y, z;

void input_params() {
    scanf("%u %u", &N, &M);
    scanf("%u %u %u %u", &w, &x, &y, &z);
}

void output_params() {
    printf("N = %u, M = %u\n", N, M);
    printf("w = %u, x = %u, y = %u, z = %u\n", w, x, y, z);
}
