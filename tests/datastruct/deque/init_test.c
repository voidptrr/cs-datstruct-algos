#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "ckit/datastruct/deque.h"

static int test_deque_init_null_pointer(void) {
    ckit_status status;

    status = ckit_deque_init(NULL, sizeof(int), NULL);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_init(NULL, ..., NULL) should return CKIT_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_deque_init_valid_pointer(void) {
    ckit_status status;
    ckit_deque q;

    status = ckit_deque_init(&q, sizeof(int), NULL);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ..., NULL) should return CKIT_OK\n");
        return 1;
    }

    if (q.buffer == NULL || q.size != 0 || q.elem_size != sizeof(int) || q.capacity != 16 ||
        q.head != 0 || q.tail != 0) {
        fprintf(stderr, "ckit_deque_init(&q, ..., NULL) returned invalid deque state\n");
        free(q.buffer);
        return 1;
    }

    free(q.buffer);
    return 0;
}

static int test_deque_init_zero_elem_size(void) {
    ckit_deque q;
    ckit_status status = ckit_deque_init(&q, 0, NULL);

    if (status != CKIT_ERR_RANGE) {
        fprintf(stderr, "ckit_deque_init(&q, 0, NULL) should return CKIT_ERR_RANGE\n");
        return 1;
    }

    return 0;
}

static int test_deque_is_empty(void) {
    ckit_deque q;
    int value = 1;

    if (ckit_deque_is_empty(NULL) != true) {
        fprintf(stderr, "ckit_deque_is_empty(NULL) should return true\n");
        return 1;
    }

    if (ckit_deque_init(&q, sizeof(int), NULL) != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ..., NULL) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_deque_is_empty(&q) != true) {
        fprintf(stderr, "ckit_deque_is_empty(&q) should return true for empty deque\n");
        free(q.buffer);
        return 1;
    }

    if (ckit_deque_push(&q, &value) != CKIT_OK) {
        fprintf(stderr, "ckit_deque_push(&q, &value) should return CKIT_OK\n");
        free(q.buffer);
        return 1;
    }

    if (ckit_deque_is_empty(&q) != false) {
        fprintf(stderr, "ckit_deque_is_empty(&q) should return false after push\n");
        free(q.buffer);
        return 1;
    }

    free(q.buffer);
    return 0;
}

int main(void) {
    if (test_deque_init_null_pointer() != 0) {
        return 1;
    }

    if (test_deque_init_valid_pointer() != 0) {
        return 1;
    }

    if (test_deque_init_zero_elem_size() != 0) {
        return 1;
    }

    if (test_deque_is_empty() != 0) {
        return 1;
    }

    return 0;
}
