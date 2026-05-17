#include <stdint.h>
#include <stdio.h>

#include "cstd/compare.h"

int main(void) {
    int32_t i32a = -2;
    int32_t i32b = 9;
    int32_t i32c = -2;

    if (!(cstd_cmp_i32(&i32a, &i32b) < 0 && cstd_cmp_i32(&i32b, &i32a) > 0 &&
          cstd_cmp_i32(&i32a, &i32c) == 0)) {
        fprintf(stderr, "cstd_cmp_i32 should provide strict weak ordering\n");
        return 1;
    }

    uint64_t u64a = 1U;
    uint64_t u64b = 2U;
    uint64_t u64c = 2U;

    if (!(cstd_cmp_u64(&u64a, &u64b) < 0 && cstd_cmp_u64(&u64b, &u64a) > 0 &&
          cstd_cmp_u64(&u64b, &u64c) == 0)) {
        fprintf(stderr, "cstd_cmp_u64 should provide strict weak ordering\n");
        return 1;
    }

    return 0;
}
