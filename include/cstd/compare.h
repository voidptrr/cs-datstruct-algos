#ifndef CSTD_COMPARE_H
#define CSTD_COMPARE_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Shared equality helpers for key matching (hashmap key_eq callbacks).
 * The size argument is honored for byte/string comparisons and ignored for
 * fixed-width scalar helpers.
 */
bool cstd_eq_bytes(const void *lhs, const void *rhs, size_t size);
bool cstd_eq_cstr(const void *lhs, const void *rhs, size_t size);
bool cstd_eq_i32(const void *lhs, const void *rhs, size_t size);
bool cstd_eq_i64(const void *lhs, const void *rhs, size_t size);
bool cstd_eq_u32(const void *lhs, const void *rhs, size_t size);
bool cstd_eq_u64(const void *lhs, const void *rhs, size_t size);

/*
 * Shared ordering helpers for container callbacks that use int-style
 * comparators (for example binary heap and future ordered utilities).
 */
int cstd_cmp_i32(const void *lhs, const void *rhs);
int cstd_cmp_i64(const void *lhs, const void *rhs);
int cstd_cmp_u32(const void *lhs, const void *rhs);
int cstd_cmp_u64(const void *lhs, const void *rhs);

#endif
