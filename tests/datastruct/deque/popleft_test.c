#include <stddef.h>
#include <stdio.h>

#include "ckit/datastruct/deque.h"

static int test_deque_popleft_null_queue(void) {
    int out = 0;

    if (ckit_deque_popleft(NULL, &out) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_popleft(NULL, &out) should return CKIT_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_deque_popleft_null_out(void) {
    ckit_status status;
    ckit_deque q;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_popleft(&q, NULL);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_popleft(&q, NULL) should return CKIT_ERR_NULL\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_popleft_empty_queue(void) {
    ckit_status status;
    ckit_deque q;
    int out = 0;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_popleft(&q, &out);
    if (status != CKIT_ERR_EMPTY) {
        fprintf(stderr, "ckit_deque_popleft on empty deque should return CKIT_ERR_EMPTY\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_popleft_fifo_order(void) {
    ckit_status status;
    ckit_deque q;
    int values[] = {7, 11, 13};
    int out = 0;
    size_t i;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        status = ckit_deque_push(&q, &values[i]);
        if (status != CKIT_OK) {
            fprintf(stderr, "ckit_deque_push should succeed before ckit_deque_popleft checks\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    for (i = 0; i < 3; i++) {
        status = ckit_deque_popleft(&q, &out);
        if (status != CKIT_OK || out != values[i]) {
            fprintf(stderr, "ckit_deque_popleft should preserve FIFO order\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    if (ckit_deque_size(&q) != 0) {
        fprintf(stderr, "ckit_deque should be empty after popping all elements\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

int main(void) {
    if (test_deque_popleft_null_queue() != 0) {
        return 1;
    }

    if (test_deque_popleft_null_out() != 0) {
        return 1;
    }

    if (test_deque_popleft_empty_queue() != 0) {
        return 1;
    }

    if (test_deque_popleft_fifo_order() != 0) {
        return 1;
    }

    return 0;
}
