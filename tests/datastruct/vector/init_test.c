#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "cstd/datastruct/vector.h"

static int test_vector_init_null_pointer(void) {
    cstd_status status;

    status = cstd_vector_init(NULL, sizeof(int));
    if (status != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_vector_init(NULL, ...) should return CSTD_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_vector_init_valid_pointer(void) {
    cstd_status status;
    cstd_vector v;

    status = cstd_vector_init(&v, sizeof(int));
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_vector_init(&v, ...) should return CSTD_OK\n");
        return 1;
    }

    if (v.buffer == NULL || v.size != 0 || v.elem_size != sizeof(int) || v.capacity != 16) {
        fprintf(stderr, "cstd_vector_init(&v, ...) returned invalid vector state\n");
        free(v.buffer);
        return 1;
    }

    free(v.buffer);
    return 0;
}

static int test_vector_init_zero_elem_size(void) {
    cstd_vector v;
    cstd_status status = cstd_vector_init(&v, 0);

    if (status != CSTD_ERR_RANGE) {
        fprintf(stderr, "cstd_vector_init(&v, 0) should return CSTD_ERR_RANGE\n");
        return 1;
    }

    return 0;
}

static int test_vector_is_empty(void) {
    cstd_vector v;
    int value = 1;

    if (cstd_vector_is_empty(NULL) != true) {
        fprintf(stderr, "cstd_vector_is_empty(NULL) should return true\n");
        return 1;
    }

    if (cstd_vector_init(&v, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_vector_init(&v, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_vector_is_empty(&v) != true) {
        fprintf(stderr, "cstd_vector_is_empty(&v) should return true for empty vector\n");
        free(v.buffer);
        return 1;
    }

    if (cstd_vector_push(&v, &value) != CSTD_OK) {
        fprintf(stderr, "cstd_vector_push(&v, &value) should return CSTD_OK\n");
        free(v.buffer);
        return 1;
    }

    if (cstd_vector_is_empty(&v) != false) {
        fprintf(stderr, "cstd_vector_is_empty(&v) should return false after push\n");
        free(v.buffer);
        return 1;
    }

    free(v.buffer);
    return 0;
}

int main(void) {
    if (test_vector_init_null_pointer() != 0) {
        return 1;
    }

    if (test_vector_init_valid_pointer() != 0) {
        return 1;
    }

    if (test_vector_init_zero_elem_size() != 0) {
        return 1;
    }

    if (test_vector_is_empty() != 0) {
        return 1;
    }

    return 0;
}
