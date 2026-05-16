#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "cstd/datastruct/queue.h"

static int test_queue_init_null_pointer(void) {
    cstd_status status;

    status = cstd_queue_init(NULL, sizeof(int));
    if (status != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_queue_init(NULL, ...) should return CSTD_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_queue_init_valid_pointer(void) {
    cstd_status status;
    cstd_queue q;

    status = cstd_queue_init(&q, sizeof(int));
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_queue_init(&q, ...) should return CSTD_OK\n");
        return 1;
    }

    if (q.buffer == NULL || q.size != 0 || q.elem_size != sizeof(int) || q.capacity != 16 ||
        q.head != 0 || q.tail != 0) {
        fprintf(stderr, "cstd_queue_init(&q, ...) returned invalid queue state\n");
        free(q.buffer);
        return 1;
    }

    free(q.buffer);
    return 0;
}

static int test_queue_init_zero_elem_size(void) {
    cstd_queue q;
    cstd_status status = cstd_queue_init(&q, 0);

    if (status != CSTD_ERR_RANGE) {
        fprintf(stderr, "cstd_queue_init(&q, 0) should return CSTD_ERR_RANGE\n");
        return 1;
    }

    return 0;
}

static int test_queue_is_empty(void) {
    cstd_queue q;
    int value = 1;

    if (cstd_queue_is_empty(NULL) != true) {
        fprintf(stderr, "cstd_queue_is_empty(NULL) should return true\n");
        return 1;
    }

    if (cstd_queue_init(&q, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_queue_init(&q, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_queue_is_empty(&q) != true) {
        fprintf(stderr, "cstd_queue_is_empty(&q) should return true for empty queue\n");
        free(q.buffer);
        return 1;
    }

    if (cstd_queue_push(&q, &value) != CSTD_OK) {
        fprintf(stderr, "cstd_queue_push(&q, &value) should return CSTD_OK\n");
        free(q.buffer);
        return 1;
    }

    if (cstd_queue_is_empty(&q) != false) {
        fprintf(stderr, "cstd_queue_is_empty(&q) should return false after push\n");
        free(q.buffer);
        return 1;
    }

    free(q.buffer);
    return 0;
}

int main(void) {
    if (test_queue_init_null_pointer() != 0) {
        return 1;
    }

    if (test_queue_init_valid_pointer() != 0) {
        return 1;
    }

    if (test_queue_init_zero_elem_size() != 0) {
        return 1;
    }

    if (test_queue_is_empty() != 0) {
        return 1;
    }

    return 0;
}
