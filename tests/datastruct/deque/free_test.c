#include <stddef.h>
#include <stdio.h>

#include "ckit/datastruct/deque.h"

static int test_deque_free_null_pointer(void) {
    ckit_status status;

    status = ckit_deque_free(NULL);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_free(NULL) should return CKIT_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_deque_free_null_buffer(void) {
    ckit_status status;
    ckit_deque q = {0};

    status = ckit_deque_free(&q);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_free(&q) with NULL buffer should return CKIT_OK\n");
        return 1;
    }

    return 0;
}

static int test_deque_free_valid_queue(void) {
    ckit_status status;
    ckit_deque q;

    status = ckit_deque_init(&q, sizeof(int), NULL);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ..., NULL) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_free(&q);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_free(&q) should return CKIT_OK\n");
        return 1;
    }

    if (q.buffer != NULL || q.size != 0 || q.capacity != 0 || q.head != 0 || q.tail != 0) {
        fprintf(stderr, "ckit_deque_free(&q) should reset deque state\n");
        return 1;
    }

    status = ckit_deque_free(&q);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_free(&q) should be idempotent\n");
        return 1;
    }

    return 0;
}

int main(void) {
    if (test_deque_free_null_pointer() != 0) {
        return 1;
    }

    if (test_deque_free_null_buffer() != 0) {
        return 1;
    }

    if (test_deque_free_valid_queue() != 0) {
        return 1;
    }

    return 0;
}
