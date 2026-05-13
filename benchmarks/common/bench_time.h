#ifndef CSTD_BENCH_TIME_H
#define CSTD_BENCH_TIME_H

/*
 * Benchmark time/stat helpers.
 * - Uses CLOCK_MONOTONIC to avoid wall-clock jumps.
 * - Provides simple summary statistics for trial samples.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

static inline uint64_t cstd_bench_now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((uint64_t)ts.tv_sec * 1000000000ULL) + (uint64_t)ts.tv_nsec;
}

static inline int cstd_bench_compare_double(const void *a, const void *b) {
    double left = *(const double *)a;
    double right = *(const double *)b;
    if (left < right) {
        return -1;
    }
    if (left > right) {
        return 1;
    }
    return 0;
}

static inline double cstd_bench_min(const double *values, size_t count) {
    double min_value = values[0];
    for (size_t i = 1; i < count; i++) {
        if (values[i] < min_value) {
            min_value = values[i];
        }
    }
    return min_value;
}

static inline double cstd_bench_median_sorted(const double *sorted_values, size_t count) {
    if ((count % 2U) == 0U) {
        size_t right_idx = count / 2U;
        size_t left_idx = right_idx - 1U;
        return (sorted_values[left_idx] + sorted_values[right_idx]) / 2.0;
    }
    return sorted_values[count / 2U];
}

static inline double cstd_bench_percentile_sorted(const double *sorted_values, size_t count,
                                                  double percentile) {
    if (count == 0U) {
        return 0.0;
    }

    /* Round up to keep percentile selection conservative on small samples. */
    double position = (percentile / 100.0) * (double)(count - 1U);
    size_t idx = (size_t)(position + 0.999999);
    if (idx >= count) {
        idx = count - 1U;
    }
    return sorted_values[idx];
}

static inline void cstd_bench_sort(double *values, size_t count) {
    qsort(values, count, sizeof(double), cstd_bench_compare_double);
}

#endif
