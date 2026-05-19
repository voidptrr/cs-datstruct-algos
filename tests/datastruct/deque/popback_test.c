#include <stddef.h>
#include <stdio.h>

#include "ckit/datastruct/deque.h"

static int test_deque_popback_null_queue(void) {
    int out = 0;

    if (ckit_deque_popback(NULL, &out) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_popback(NULL, &out) should return CKIT_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_deque_popback_null_out(void) {
    ckit_status status;
    ckit_deque q;

    status = ckit_deque_init(&q, sizeof(int), NULL);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ..., NULL) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_popback(&q, NULL);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_popback(&q, NULL) should return CKIT_ERR_NULL\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_popback_empty_queue(void) {
    ckit_status status;
    ckit_deque q;
    int out = 0;

    status = ckit_deque_init(&q, sizeof(int), NULL);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ..., NULL) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_popback(&q, &out);
    if (status != CKIT_ERR_EMPTY) {
        fprintf(stderr, "ckit_deque_popback on empty deque should return CKIT_ERR_EMPTY\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_popback_wraps_tail_backward(void) {
    ckit_status status;
    ckit_deque q;
    int out = 0;
    int i;
    size_t initial_capacity;

    status = ckit_deque_init(&q, sizeof(int), NULL);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ..., NULL) should return CKIT_OK\n");
        return 1;
    }

    initial_capacity = q.capacity;

    for (i = 0; i < (int)initial_capacity; i++) {
        int value = i;
        status = ckit_deque_push(&q, &value);
        if (status != CKIT_OK) {
            fprintf(stderr, "ckit_deque_push should fill deque capacity\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    status = ckit_deque_popback(&q, &out);
    if (status != CKIT_OK || out != (int)(initial_capacity - 1)) {
        fprintf(stderr, "ckit_deque_popback should return the last pushed element\n");
        ckit_deque_free(&q);
        return 1;
    }

    if (q.tail != initial_capacity - 1 || q.size != initial_capacity - 1) {
        fprintf(stderr, "ckit_deque_popback should move tail backward by one\n");
        ckit_deque_free(&q);
        return 1;
    }

    for (i = 0; i < (int)(initial_capacity - 1); i++) {
        status = ckit_deque_popleft(&q, &out);
        if (status != CKIT_OK || out != i) {
            fprintf(stderr, "ckit_deque should preserve remaining FIFO order after popback\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    ckit_deque_free(&q);
    return 0;
}

int main(void) {
    if (test_deque_popback_null_queue() != 0) {
        return 1;
    }

    if (test_deque_popback_null_out() != 0) {
        return 1;
    }

    if (test_deque_popback_empty_queue() != 0) {
        return 1;
    }

    if (test_deque_popback_wraps_tail_backward() != 0) {
        return 1;
    }

    return 0;
}
