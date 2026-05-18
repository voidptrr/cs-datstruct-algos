#include <stdio.h>

#include "ckit/datastruct/binary_heap.h"

static int cmp_int_asc(const void *a, const void *b) {
    int lhs = *(const int *)a;
    int rhs = *(const int *)b;
    return (lhs > rhs) - (lhs < rhs);
}

int main(void) {
    ckit_binary_heap heap;
    int value = 1;

    if (ckit_binary_heap_free(NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_binary_heap_free(NULL) should return CKIT_ERR_NULL\n");
        return 1;
    }

    if (ckit_binary_heap_init(&heap, sizeof(int), cmp_int_asc) != CKIT_OK) {
        fprintf(stderr, "ckit_binary_heap_init should return CKIT_OK\n");
        return 1;
    }

    ckit_binary_heap_push(&heap, &value);

    if (ckit_binary_heap_free(&heap) != CKIT_OK) {
        fprintf(stderr, "ckit_binary_heap_free should return CKIT_OK\n");
        return 1;
    }

    if (ckit_binary_heap_size(&heap) != 0U || heap.cmp != NULL) {
        fprintf(stderr, "ckit_binary_heap_free should reset heap state\n");
        return 1;
    }

    if (ckit_binary_heap_free(&heap) != CKIT_OK) {
        fprintf(stderr, "ckit_binary_heap_free should be idempotent\n");
        return 1;
    }

    return 0;
}
