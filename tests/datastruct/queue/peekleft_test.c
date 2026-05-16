#include <stdio.h>

#include "cstd/datastruct/queue.h"

static int test_queue_peekleft_null_args(void) {
    cstd_queue q;
    int out = 0;

    if (cstd_queue_peekleft(NULL, &out) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_queue_peekleft(NULL, &out) should return CSTD_ERR_NULL\n");
        return 1;
    }

    if (cstd_queue_init(&q, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_queue_init(&q, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_queue_peekleft(&q, NULL) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_queue_peekleft(&q, NULL) should return CSTD_ERR_NULL\n");
        cstd_queue_free(&q);
        return 1;
    }

    cstd_queue_free(&q);
    return 0;
}

static int test_queue_peekleft_empty_queue(void) {
    cstd_queue q;
    int out = 0;

    if (cstd_queue_init(&q, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_queue_init(&q, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_queue_peekleft(&q, &out) != CSTD_ERR_EMPTY) {
        fprintf(stderr, "cstd_queue_peekleft on empty queue should return CSTD_ERR_EMPTY\n");
        cstd_queue_free(&q);
        return 1;
    }

    cstd_queue_free(&q);
    return 0;
}

static int test_queue_peekleft_does_not_remove(void) {
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

    if (cstd_queue_peekleft(&q, &out) != CSTD_OK || out != first) {
        fprintf(stderr, "cstd_queue_peekleft should return the front element\n");
        cstd_queue_free(&q);
        return 1;
    }

    if (cstd_queue_size(&q) != 2) {
        fprintf(stderr, "cstd_queue_peekleft should not change queue size\n");
        cstd_queue_free(&q);
        return 1;
    }

    if (cstd_queue_popleft(&q, &out) != CSTD_OK || out != first) {
        fprintf(stderr, "cstd_queue_peekleft should not remove front element\n");
        cstd_queue_free(&q);
        return 1;
    }

    cstd_queue_free(&q);
    return 0;
}

int main(void) {
    if (test_queue_peekleft_null_args() != 0) {
        return 1;
    }

    if (test_queue_peekleft_empty_queue() != 0) {
        return 1;
    }

    if (test_queue_peekleft_does_not_remove() != 0) {
        return 1;
    }

    return 0;
}
