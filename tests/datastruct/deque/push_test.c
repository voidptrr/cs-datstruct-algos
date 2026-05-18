#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "ckit/datastruct/deque.h"

static int test_deque_push_appends_value(void) {
    ckit_status status;
    ckit_deque q;
    int value = 42;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_push(&q, &value);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_push(&q, &value) should return CKIT_OK\n");
        free(q.buffer);
        return 1;
    }

    if (q.size != 1) {
        fprintf(stderr, "deque_push should increment deque size\n");
        free(q.buffer);
        return 1;
    }

    if (q.head != 0 || q.tail != 1) {
        fprintf(stderr, "deque_push should update head/tail correctly\n");
        free(q.buffer);
        return 1;
    }

    if (((int *)q.buffer)[0] != value) {
        fprintf(stderr, "deque_push should copy pushed value into buffer\n");
        free(q.buffer);
        return 1;
    }

    free(q.buffer);
    return 0;
}

static int test_deque_push_null_pointers(void) {
    ckit_status status;
    ckit_deque q;
    int value = 1;

    status = ckit_deque_push(NULL, &value);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_push(NULL, &value) should return CKIT_ERR_NULL\n");
        return 1;
    }

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_push(&q, NULL);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_push(&q, NULL) should return CKIT_ERR_NULL\n");
        free(q.buffer);
        return 1;
    }

    free(q.buffer);
    return 0;
}

static int test_deque_push_wraparound_growth(void) {
    ckit_status status;
    ckit_deque q;
    int pushed = 99;
    int popped = 0;
    int i;
    size_t initial_capacity;
    size_t pop_count;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    initial_capacity = q.capacity;
    pop_count = initial_capacity / 2;

    for (i = 0; i < (int)initial_capacity; i++) {
        int value = i;
        status = ckit_deque_push(&q, &value);
        if (status != CKIT_OK) {
            fprintf(stderr, "ckit_deque_push should fill deque up to capacity\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    for (i = 0; i < (int)pop_count; i++) {
        status = ckit_deque_popleft(&q, &popped);
        if (status != CKIT_OK || popped != i) {
            fprintf(stderr, "ckit_deque_popleft should dequeue initial FIFO values\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    for (i = (int)initial_capacity; i < (int)(initial_capacity + pop_count); i++) {
        int value = i;
        status = ckit_deque_push(&q, &value);
        if (status != CKIT_OK) {
            fprintf(stderr, "ckit_deque_push should wrap and refill deque\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    status = ckit_deque_push(&q, &pushed);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_push should succeed on wrapped full deque\n");
        ckit_deque_free(&q);
        return 1;
    }

    if (q.capacity != initial_capacity * 2 || q.size != initial_capacity + 1 || q.head != 0 ||
        q.tail != initial_capacity + 1) {
        fprintf(stderr, "ckit_deque_push should grow and normalize wrapped deque indices\n");
        ckit_deque_free(&q);
        return 1;
    }

    for (i = (int)pop_count; i < (int)(initial_capacity + pop_count); i++) {
        status = ckit_deque_popleft(&q, &popped);
        if (status != CKIT_OK || popped != i) {
            fprintf(stderr, "ckit_deque should preserve FIFO order after wrapped growth\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    status = ckit_deque_popleft(&q, &popped);
    if (status != CKIT_OK || popped != pushed) {
        fprintf(stderr, "ckit_deque should keep newly pushed element after growth\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

int main(void) {
    if (test_deque_push_appends_value() != 0) {
        return 1;
    }

    if (test_deque_push_null_pointers() != 0) {
        return 1;
    }

    if (test_deque_push_wraparound_growth() != 0) {
        return 1;
    }

    return 0;
}
