#include <stdio.h>

#include "ckit/datastruct/deque.h"

static int test_deque_peekleft_null_args(void) {
    ckit_deque q;
    int out = 0;

    if (ckit_deque_peekleft(NULL, &out) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_peekleft(NULL, &out) should return CKIT_ERR_NULL\n");
        return 1;
    }

    if (ckit_deque_init(&q, sizeof(int)) != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_deque_peekleft(&q, NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_peekleft(&q, NULL) should return CKIT_ERR_NULL\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_peekleft_empty_queue(void) {
    ckit_deque q;
    int out = 0;

    if (ckit_deque_init(&q, sizeof(int)) != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_deque_peekleft(&q, &out) != CKIT_ERR_EMPTY) {
        fprintf(stderr, "ckit_deque_peekleft on empty deque should return CKIT_ERR_EMPTY\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_peekleft_does_not_remove(void) {
    ckit_deque q;
    int first = 3;
    int second = 7;
    int out = 0;

    if (ckit_deque_init(&q, sizeof(int)) != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_deque_push(&q, &first) != CKIT_OK || ckit_deque_push(&q, &second) != CKIT_OK) {
        fprintf(stderr, "ckit_deque_push should succeed before peek checks\n");
        ckit_deque_free(&q);
        return 1;
    }

    if (ckit_deque_peekleft(&q, &out) != CKIT_OK || out != first) {
        fprintf(stderr, "ckit_deque_peekleft should return the front element\n");
        ckit_deque_free(&q);
        return 1;
    }

    if (ckit_deque_size(&q) != 2) {
        fprintf(stderr, "ckit_deque_peekleft should not change deque size\n");
        ckit_deque_free(&q);
        return 1;
    }

    if (ckit_deque_popleft(&q, &out) != CKIT_OK || out != first) {
        fprintf(stderr, "ckit_deque_peekleft should not remove front element\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

int main(void) {
    if (test_deque_peekleft_null_args() != 0) {
        return 1;
    }

    if (test_deque_peekleft_empty_queue() != 0) {
        return 1;
    }

    if (test_deque_peekleft_does_not_remove() != 0) {
        return 1;
    }

    return 0;
}
