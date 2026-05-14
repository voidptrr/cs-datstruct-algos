#include <stdint.h>
#include <stdio.h>

#include "common/bench_report.h"
#include "datastruct/vector.h"

#define CSTD_BENCH_WARMUP_OPS 100000ULL
#define CSTD_BENCH_MEASURED_OPS 10000000ULL
#define CSTD_BENCH_TRIALS 30U

static cstd_status run_vector_steady_trial(uint64_t ops, double *ns_per_op) {
    cstd_vector vector;
    cstd_status status = cstd_vector_init(&vector, sizeof(int));
    if (status != CSTD_OK) {
        return status;
    }

    /* Prefill before timing so steady-state avoids empty-vector edges. */
    for (int i = 0; i < 16; i++) {
        int value = i;
        if (cstd_vector_push(&vector, &value) != CSTD_OK) {
            cstd_vector_free(&vector);
            return CSTD_ERR_STATE;
        }
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        int value = (int)i;
        int out;
        if (cstd_vector_pop(&vector, &out) != CSTD_OK || cstd_vector_push(&vector, &value) != CSTD_OK) {
            cstd_vector_free(&vector);
            return CSTD_ERR_STATE;
        }
    }
    uint64_t end = cstd_bench_now_ns();

    cstd_vector_free(&vector);
    /* Each loop iteration performs 2 vector operations: pop + push. */
    *ns_per_op = (double)(end - start) / (double)(ops * 2ULL);
    return CSTD_OK;
}

static cstd_status run_vector_growth_trial(uint64_t ops, double *ns_per_op) {
    cstd_vector vector;
    cstd_status status = cstd_vector_init(&vector, sizeof(int));
    if (status != CSTD_OK) {
        return status;
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        int value = (int)i;
        if (cstd_vector_push(&vector, &value) != CSTD_OK) {
            cstd_vector_free(&vector);
            return CSTD_ERR_STATE;
        }
        if ((i & 1ULL) == 1ULL) {
            int out;
            if (cstd_vector_pop(&vector, &out) != CSTD_OK) {
                cstd_vector_free(&vector);
                return CSTD_ERR_STATE;
            }
        }
    }

    while (cstd_vector_size(&vector) > 0U) {
        int out;
        if (cstd_vector_pop(&vector, &out) != CSTD_OK) {
            cstd_vector_free(&vector);
            return CSTD_ERR_STATE;
        }
    }
    uint64_t end = cstd_bench_now_ns();

    cstd_vector_free(&vector);
    /* push count = ops, pop count = ops/2 in-loop + ops/2 during drain. */
    *ns_per_op = (double)(end - start) / (double)(ops + (ops / 2ULL) + (ops / 2ULL));
    return CSTD_OK;
}

int main(void) {
    cstd_bench_case cases[] = {
        {.name = "steady_push_pop", .trial_fn = run_vector_steady_trial},
        {.name = "growth_push_pop", .trial_fn = run_vector_growth_trial},
    };
    cstd_bench_result results[sizeof(cases) / sizeof(cases[0])];

    for (size_t i = 0; i < (sizeof(cases) / sizeof(cases[0])); i++) {
        if (cstd_bench_run_case(&cases[i], CSTD_BENCH_WARMUP_OPS, CSTD_BENCH_MEASURED_OPS,
                                CSTD_BENCH_TRIALS, &results[i]) != CSTD_OK) {
            return 1;
        }
    }

    cstd_bench_print_table("vector", cases, results, sizeof(cases) / sizeof(cases[0]),
                           CSTD_BENCH_MEASURED_OPS, CSTD_BENCH_TRIALS);

    return 0;
}
