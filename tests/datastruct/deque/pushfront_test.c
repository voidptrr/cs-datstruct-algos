#include <stddef.h>
#include <stdio.h>

#include "ckit/datastruct/deque.h"

static int test_deque_pushfront_null_queue(void) {
    int value = 1;

    if (ckit_deque_pushfront(NULL, &value) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_pushfront(NULL, &value) should return CKIT_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_deque_pushfront_null_element(void) {
    enum ckit_status status;
    struct ckit_deque q;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_pushfront(&q, NULL);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_deque_pushfront(&q, NULL) should return CKIT_ERR_NULL\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_pushfront_empty_queue(void) {
    enum ckit_status status;
    struct ckit_deque q;
    int value = 42;
    int out = 0;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_deque_pushfront(&q, &value);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_pushfront(&q, &value) should return CKIT_OK\n");
        ckit_deque_free(&q);
        return 1;
    }

    if (ckit_deque_size(&q) != 1) {
        fprintf(stderr, "ckit_deque_pushfront should increment deque size\n");
        ckit_deque_free(&q);
        return 1;
    }

    status = ckit_deque_popleft(&q, &out);
    if (status != CKIT_OK || out != value) {
        fprintf(stderr, "ckit_deque_pushfront should place value at deque front\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_pushfront_preserves_front_order(void) {
    enum ckit_status status;
    struct ckit_deque q;
    int first = 1;
    int second = 2;
    int front = 0;
    int out = 0;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_deque_push(&q, &first) != CKIT_OK || ckit_deque_push(&q, &second) != CKIT_OK ||
        ckit_deque_pushfront(&q, &front) != CKIT_OK) {
        fprintf(stderr, "deque pushes should succeed before order checks\n");
        ckit_deque_free(&q);
        return 1;
    }

    status = ckit_deque_popleft(&q, &out);
    if (status != CKIT_OK || out != front) {
        fprintf(stderr, "ckit_deque_pushfront should return new front first\n");
        ckit_deque_free(&q);
        return 1;
    }

    status = ckit_deque_popleft(&q, &out);
    if (status != CKIT_OK || out != first) {
        fprintf(stderr, "ckit_deque should preserve existing order after pushfront\n");
        ckit_deque_free(&q);
        return 1;
    }

    status = ckit_deque_popleft(&q, &out);
    if (status != CKIT_OK || out != second) {
        fprintf(stderr, "ckit_deque should keep tail order after pushfront\n");
        ckit_deque_free(&q);
        return 1;
    }

    ckit_deque_free(&q);
    return 0;
}

static int test_deque_pushfront_wraparound_growth(void) {
    enum ckit_status status;
    struct ckit_deque q;
    size_t initial_capacity;
    int out = 0;

    status = ckit_deque_init(&q, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_deque_init(&q, ...) should return CKIT_OK\n");
        return 1;
    }

    initial_capacity = q.capacity;

    for (int i = 0; i < (int)initial_capacity; i++) {
        int value = i;
        if (ckit_deque_push(&q, &value) != CKIT_OK) {
            fprintf(stderr, "ckit_deque_push should fill deque capacity\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    for (int i = 0; i < (int)(initial_capacity / 2); i++) {
        if (ckit_deque_popleft(&q, &out) != CKIT_OK || out != i) {
            fprintf(stderr, "ckit_deque_popleft should consume initial prefix\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    for (int i = (int)initial_capacity; i < (int)(initial_capacity + (initial_capacity / 2)); i++) {
        int value = i;
        if (ckit_deque_push(&q, &value) != CKIT_OK) {
            fprintf(stderr, "ckit_deque_push should wrap and refill deque\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    {
        int front = -1;
        status = ckit_deque_pushfront(&q, &front);
        if (status != CKIT_OK) {
            fprintf(stderr, "ckit_deque_pushfront should grow wrapped full deque\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    if (q.capacity != initial_capacity * 2 || q.size != initial_capacity + 1) {
        fprintf(stderr, "ckit_deque_pushfront should grow capacity and preserve size\n");
        ckit_deque_free(&q);
        return 1;
    }

    if (ckit_deque_popleft(&q, &out) != CKIT_OK || out != -1) {
        fprintf(stderr, "ckit_deque_pushfront should keep inserted front after growth\n");
        ckit_deque_free(&q);
        return 1;
    }

    for (int i = (int)(initial_capacity / 2); i < (int)(initial_capacity + (initial_capacity / 2));
         i++) {
        if (ckit_deque_popleft(&q, &out) != CKIT_OK || out != i) {
            fprintf(stderr,
                    "ckit_deque_pushfront should preserve logical FIFO order after growth\n");
            ckit_deque_free(&q);
            return 1;
        }
    }

    ckit_deque_free(&q);
    return 0;
}

int main(void) {
    if (test_deque_pushfront_null_queue() != 0) {
        return 1;
    }

    if (test_deque_pushfront_null_element() != 0) {
        return 1;
    }

    if (test_deque_pushfront_empty_queue() != 0) {
        return 1;
    }

    if (test_deque_pushfront_preserves_front_order() != 0) {
        return 1;
    }

    if (test_deque_pushfront_wraparound_growth() != 0) {
        return 1;
    }

    return 0;
}
