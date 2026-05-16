#ifndef CSTD_BENCH_REPORT_H
#define CSTD_BENCH_REPORT_H

/*
 * Benchmark reporting helpers.
 * A benchmark defines named trial functions (cases), runs warmup + measured
 * trials, then prints min/median/p95 and median-based throughput.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "bench_time.h"
#include "cstd/status.h"

typedef struct {
    const char *name;
    cstd_status (*trial_fn)(uint64_t ops, double *ns_per_op);
} cstd_bench_case;

typedef struct {
    double min_ns;
    double median_ns;
    double p95_ns;
    double ops_per_sec;
} cstd_bench_result;

static inline cstd_status cstd_bench_run_case(const cstd_bench_case *bench_case,
                                              uint64_t warmup_ops, uint64_t measured_ops,
                                              size_t trials, cstd_bench_result *out_result) {
    double ns_per_op[64];
    size_t len = sizeof(ns_per_op) / sizeof(ns_per_op[0]);

    if (trials == 0U || trials > len) {
        fprintf(stderr, "Invalid trial count: %zu\n", trials);
        return CSTD_ERR_RANGE;
    }

    /* Warmup is intentionally excluded from reported metrics. */
    if (bench_case->trial_fn(warmup_ops, &ns_per_op[0]) != CSTD_OK) {
        fprintf(stderr, "Warmup failed for %s\n", bench_case->name);
        return CSTD_ERR_STATE;
    }

    for (size_t i = 0; i < trials; i++) {
        if (bench_case->trial_fn(measured_ops, &ns_per_op[i]) != CSTD_OK) {
            fprintf(stderr, "Trial %zu failed for %s\n", i, bench_case->name);
            return CSTD_ERR_STATE;
        }
    }

    out_result->min_ns = cstd_bench_min(ns_per_op, trials);
    cstd_bench_sort(ns_per_op, trials);
    out_result->median_ns = cstd_bench_median_sorted(ns_per_op, trials);
    /* p95 highlights tail behavior across repeated trials. */
    out_result->p95_ns = cstd_bench_percentile_sorted(ns_per_op, trials, 95.0);
    out_result->ops_per_sec = 1000000000.0 / out_result->median_ns;

    return CSTD_OK;
}

static inline void cstd_bench_print_table(const char *title, const cstd_bench_case *cases,
                                          const cstd_bench_result *results, size_t case_count,
                                          uint64_t measured_ops, size_t trials) {
    printf("\n%s benchmark\n", title);
    printf("ops=%llu trials=%zu\n", (unsigned long long)measured_ops, trials);
    printf("%-24s | %10s | %12s | %10s | %12s\n", "case", "min ns/op", "median ns/op",
           "p95 ns/op", "ops/sec");
    printf("%-24s-+-%10s-+-%12s-+-%10s-+-%12s\n", "------------------------", "----------",
           "------------", "----------", "------------");

    for (size_t i = 0; i < case_count; i++) {
        printf("%-24s | %10.3f | %12.3f | %10.3f | %12.0f\n", cases[i].name, results[i].min_ns,
               results[i].median_ns, results[i].p95_ns, results[i].ops_per_sec);
    }
}

#endif
