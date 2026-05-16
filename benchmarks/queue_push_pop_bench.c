#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "common/bench_payload.h"
#include "common/bench_report.h"
#include "cstd/datastruct/queue.h"

#define CSTD_BENCH_WARMUP_OPS 100000ULL
#define CSTD_BENCH_MEASURED_OPS 10000000ULL
#define CSTD_BENCH_TRIALS 30U

static cstd_status run_queue_steady_trial(uint64_t ops, double *ns_per_op) {
    cstd_queue queue;
    cstd_status status = cstd_queue_init(&queue, sizeof(cstd_bench_payload));
    if (status != CSTD_OK) {
        return status;
    }

    /* Prefill before timing so steady-state avoids empty-queue edges. */
    for (int i = 0; i < 16; i++) {
        cstd_bench_payload value = cstd_bench_payload_make((uint64_t)i);
        if (cstd_queue_push(&queue, &value) != CSTD_OK) {
            cstd_queue_free(&queue);
            return CSTD_ERR_STATE;
        }
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        cstd_bench_payload out;
        cstd_bench_payload value = cstd_bench_payload_make(i);
        if (cstd_queue_popleft(&queue, &out) != CSTD_OK || cstd_queue_push(&queue, &value) != CSTD_OK) {
            cstd_queue_free(&queue);
            return CSTD_ERR_STATE;
        }
    }
    uint64_t end = cstd_bench_now_ns();

    cstd_queue_free(&queue);
    /* Each loop iteration performs 2 queue operations: popleft + push. */
    *ns_per_op = (double)(end - start) / (double)(ops * 2ULL);
    return CSTD_OK;
}

static cstd_status run_queue_growth_trial(uint64_t ops, double *ns_per_op) {
    cstd_queue queue;
    cstd_status status = cstd_queue_init(&queue, sizeof(cstd_bench_payload));
    if (status != CSTD_OK) {
        return status;
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        cstd_bench_payload value = cstd_bench_payload_make(i);
        if (cstd_queue_push(&queue, &value) != CSTD_OK) {
            cstd_queue_free(&queue);
            return CSTD_ERR_STATE;
        }
        if ((i & 1ULL) == 1ULL) {
            cstd_bench_payload out;
            if (cstd_queue_popleft(&queue, &out) != CSTD_OK) {
                cstd_queue_free(&queue);
                return CSTD_ERR_STATE;
            }
        }
    }

    while (cstd_queue_size(&queue) > 0U) {
        cstd_bench_payload out;
        if (cstd_queue_popleft(&queue, &out) != CSTD_OK) {
            cstd_queue_free(&queue);
            return CSTD_ERR_STATE;
        }
    }
    uint64_t end = cstd_bench_now_ns();

    cstd_queue_free(&queue);
    /* push count = ops, pop count = ops/2 in-loop + ops/2 during drain. */
    *ns_per_op = (double)(end - start) / (double)(ops + (ops / 2ULL) + (ops / 2ULL));
    return CSTD_OK;
}

static cstd_status run_queue_steady_pushfront_trial(uint64_t ops, double *ns_per_op) {
    cstd_queue queue;
    cstd_status status = cstd_queue_init(&queue, sizeof(cstd_bench_payload));
    if (status != CSTD_OK) {
        return status;
    }

    /* Prefill before timing so steady-state avoids empty-queue edges. */
    for (int i = 0; i < 16; i++) {
        cstd_bench_payload value = cstd_bench_payload_make((uint64_t)i);
        if (cstd_queue_pushfront(&queue, &value) != CSTD_OK) {
            cstd_queue_free(&queue);
            return CSTD_ERR_STATE;
        }
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        cstd_bench_payload out;
        cstd_bench_payload value = cstd_bench_payload_make(i);
        if (cstd_queue_popback(&queue, &out) != CSTD_OK ||
            cstd_queue_pushfront(&queue, &value) != CSTD_OK) {
            cstd_queue_free(&queue);
            return CSTD_ERR_STATE;
        }
    }
    uint64_t end = cstd_bench_now_ns();

    cstd_queue_free(&queue);
    /* Each loop iteration performs 2 queue operations: popback + pushfront. */
    *ns_per_op = (double)(end - start) / (double)(ops * 2ULL);
    return CSTD_OK;
}

static cstd_status run_queue_growth_pushfront_trial(uint64_t ops, double *ns_per_op) {
    cstd_queue queue;
    cstd_status status = cstd_queue_init(&queue, sizeof(cstd_bench_payload));
    if (status != CSTD_OK) {
        return status;
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        cstd_bench_payload value = cstd_bench_payload_make(i);
        if (cstd_queue_pushfront(&queue, &value) != CSTD_OK) {
            cstd_queue_free(&queue);
            return CSTD_ERR_STATE;
        }
        if ((i & 1ULL) == 1ULL) {
            cstd_bench_payload out;
            if (cstd_queue_popback(&queue, &out) != CSTD_OK) {
                cstd_queue_free(&queue);
                return CSTD_ERR_STATE;
            }
        }
    }

    while (cstd_queue_size(&queue) > 0U) {
        cstd_bench_payload out;
        if (cstd_queue_popback(&queue, &out) != CSTD_OK) {
            cstd_queue_free(&queue);
            return CSTD_ERR_STATE;
        }
    }
    uint64_t end = cstd_bench_now_ns();

    cstd_queue_free(&queue);
    /* push count = ops, pop count = ops/2 in-loop + ops/2 during drain. */
    *ns_per_op = (double)(end - start) / (double)(ops + (ops / 2ULL) + (ops / 2ULL));
    return CSTD_OK;
}

int main(void) {
    cstd_bench_case cases[] = {
        {.name = "steady_push_pop", .trial_fn = run_queue_steady_trial},
        {.name = "growth_push_pop", .trial_fn = run_queue_growth_trial},
        {.name = "steady_pushfront_popback", .trial_fn = run_queue_steady_pushfront_trial},
        {.name = "growth_pushfront_popback", .trial_fn = run_queue_growth_pushfront_trial},
    };
    cstd_bench_result results[sizeof(cases) / sizeof(cases[0])];

    for (size_t i = 0; i < (sizeof(cases) / sizeof(cases[0])); i++) {
        if (cstd_bench_run_case(&cases[i], CSTD_BENCH_WARMUP_OPS, CSTD_BENCH_MEASURED_OPS,
                                CSTD_BENCH_TRIALS, &results[i]) != CSTD_OK) {
            return 1;
        }
    }

    cstd_bench_print_table("queue", cases, results, sizeof(cases) / sizeof(cases[0]),
                           CSTD_BENCH_MEASURED_OPS, CSTD_BENCH_TRIALS);

    return 0;
}
