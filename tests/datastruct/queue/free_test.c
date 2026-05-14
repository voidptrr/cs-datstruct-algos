#include <stddef.h>
#include <stdio.h>

#include "datastruct/queue.h"

static int test_queue_free_null_pointer(void) {
    cstd_status status;

    status = cstd_queue_free(NULL);
    if (status != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_queue_free(NULL) should return CSTD_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_queue_free_null_buffer(void) {
    cstd_status status;
    cstd_queue q = {0};

    status = cstd_queue_free(&q);
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_queue_free(&q) with NULL buffer should return CSTD_OK\n");
        return 1;
    }

    return 0;
}

static int test_queue_free_valid_queue(void) {
    cstd_status status;
    cstd_queue q;

    status = cstd_queue_init(&q, sizeof(int));
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_queue_init(&q, ...) should return CSTD_OK\n");
        return 1;
    }

    status = cstd_queue_free(&q);
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_queue_free(&q) should return CSTD_OK\n");
        return 1;
    }

    if (q.buffer != NULL || q.size != 0 || q.capacity != 0 || q.head != 0 || q.tail != 0) {
        fprintf(stderr, "cstd_queue_free(&q) should reset queue state\n");
        return 1;
    }

    status = cstd_queue_free(&q);
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_queue_free(&q) should be idempotent\n");
        return 1;
    }

    return 0;
}

int main(void) {
    if (test_queue_free_null_pointer() != 0) {
        return 1;
    }

    if (test_queue_free_null_buffer() != 0) {
        return 1;
    }

    if (test_queue_free_valid_queue() != 0) {
        return 1;
    }

    return 0;
}
