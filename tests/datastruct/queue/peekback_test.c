#include <stdio.h>

#include "cstd/datastruct/queue.h"

static int test_queue_peekback_null_args(void) {
    cstd_queue q;
    int out = 0;

    if (cstd_queue_peekback(NULL, &out) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_queue_peekback(NULL, &out) should return CSTD_ERR_NULL\n");
        return 1;
    }

    if (cstd_queue_init(&q, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_queue_init(&q, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_queue_peekback(&q, NULL) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_queue_peekback(&q, NULL) should return CSTD_ERR_NULL\n");
        cstd_queue_free(&q);
        return 1;
    }

    cstd_queue_free(&q);
    return 0;
}

static int test_queue_peekback_empty_queue(void) {
    cstd_queue q;
    int out = 0;

    if (cstd_queue_init(&q, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_queue_init(&q, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_queue_peekback(&q, &out) != CSTD_ERR_EMPTY) {
        fprintf(stderr, "cstd_queue_peekback on empty queue should return CSTD_ERR_EMPTY\n");
        cstd_queue_free(&q);
        return 1;
    }

    cstd_queue_free(&q);
    return 0;
}

static int test_queue_peekback_does_not_remove(void) {
    cstd_queue q;
    int first = 3;
    int second = 7;
    int out = 0;

    if (cstd_queue_init(&q, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_queue_init(&q, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_queue_push(&q, &first) != CSTD_OK || cstd_queue_push(&q, &second) != CSTD_OK) {
        fprintf(stderr, "cstd_queue_push should succeed before peek checks\n");
        cstd_queue_free(&q);
        return 1;
    }

    if (cstd_queue_peekback(&q, &out) != CSTD_OK || out != second) {
        fprintf(stderr, "cstd_queue_peekback should return the back element\n");
        cstd_queue_free(&q);
        return 1;
    }

    if (cstd_queue_size(&q) != 2) {
        fprintf(stderr, "cstd_queue_peekback should not change queue size\n");
        cstd_queue_free(&q);
        return 1;
    }

    if (cstd_queue_popback(&q, &out) != CSTD_OK || out != second) {
        fprintf(stderr, "cstd_queue_peekback should not remove back element\n");
        cstd_queue_free(&q);
        return 1;
    }

    cstd_queue_free(&q);
    return 0;
}

int main(void) {
    if (test_queue_peekback_null_args() != 0) {
        return 1;
    }

    if (test_queue_peekback_empty_queue() != 0) {
        return 1;
    }

    if (test_queue_peekback_does_not_remove() != 0) {
        return 1;
    }

    return 0;
}
