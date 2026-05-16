#include <stdint.h>

#include "common/bench_payload.h"
#include "common/bench_report.h"
#include "cstd/datastruct/linked_list.h"

#define CSTD_BENCH_WARMUP_OPS 50000ULL
#define CSTD_BENCH_MEASURED_OPS 1000000ULL
#define CSTD_BENCH_TRIALS 30U

static cstd_status run_linked_list_steady_push_trial(uint64_t ops, double *ns_per_op) {
    cstd_linked_list list;
    cstd_status status = cstd_linked_list_init(&list, sizeof(cstd_bench_payload));
    if (status != CSTD_OK) {
        return status;
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        cstd_bench_payload value = cstd_bench_payload_make(i);
        if (cstd_linked_list_push(&list, &value) != CSTD_OK) {
            cstd_linked_list_free(&list);
            return CSTD_ERR_STATE;
        }
    }
    uint64_t end = cstd_bench_now_ns();

    cstd_linked_list_free(&list);
    *ns_per_op = (double)(end - start) / (double)ops;
    return CSTD_OK;
}

static cstd_status run_linked_list_push_plus_free_trial(uint64_t ops, double *ns_per_op) {
    cstd_linked_list list;
    cstd_status status = cstd_linked_list_init(&list, sizeof(cstd_bench_payload));
    if (status != CSTD_OK) {
        return status;
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        cstd_bench_payload value = cstd_bench_payload_make(i);
        if (cstd_linked_list_push(&list, &value) != CSTD_OK) {
            cstd_linked_list_free(&list);
            return CSTD_ERR_STATE;
        }
    }
    if (cstd_linked_list_free(&list) != CSTD_OK) {
        return CSTD_ERR_STATE;
    }
    uint64_t end = cstd_bench_now_ns();

    *ns_per_op = (double)(end - start) / (double)ops;
    return CSTD_OK;
}

static cstd_status run_linked_list_steady_pushfront_popleft_trial(uint64_t ops, double *ns_per_op) {
    cstd_linked_list list;
    cstd_status status = cstd_linked_list_init(&list, sizeof(cstd_bench_payload));
    if (status != CSTD_OK) {
        return status;
    }

    for (int i = 0; i < 16; i++) {
        cstd_bench_payload value = cstd_bench_payload_make((uint64_t)i);
        if (cstd_linked_list_pushfront(&list, &value) != CSTD_OK) {
            cstd_linked_list_free(&list);
            return CSTD_ERR_STATE;
        }
    }

    uint64_t start = cstd_bench_now_ns();
    for (uint64_t i = 0; i < ops; i++) {
        cstd_bench_payload out;
        cstd_bench_payload value = cstd_bench_payload_make(i);
        if (cstd_linked_list_popleft(&list, &out) != CSTD_OK ||
            cstd_linked_list_pushfront(&list, &value) != CSTD_OK) {
            cstd_linked_list_free(&list);
            return CSTD_ERR_STATE;
        }
    }
    uint64_t end = cstd_bench_now_ns();

    cstd_linked_list_free(&list);
    *ns_per_op = (double)(end - start) / (double)ops;
    return CSTD_OK;
}

int main(void) {
    cstd_bench_case cases[] = {
        {.name = "steady_push", .trial_fn = run_linked_list_steady_push_trial},
        {.name = "push_plus_free", .trial_fn = run_linked_list_push_plus_free_trial},
        {.name = "steady_pushfront_popleft", .trial_fn = run_linked_list_steady_pushfront_popleft_trial},
    };
    cstd_bench_result results[sizeof(cases) / sizeof(cases[0])];

    for (size_t i = 0; i < (sizeof(cases) / sizeof(cases[0])); i++) {
        if (cstd_bench_run_case(&cases[i], CSTD_BENCH_WARMUP_OPS, CSTD_BENCH_MEASURED_OPS,
                                CSTD_BENCH_TRIALS, &results[i]) != CSTD_OK) {
            return 1;
        }
    }

    cstd_bench_print_table("linked_list", cases, results, sizeof(cases) / sizeof(cases[0]),
                           CSTD_BENCH_MEASURED_OPS, CSTD_BENCH_TRIALS);

    return 0;
}
