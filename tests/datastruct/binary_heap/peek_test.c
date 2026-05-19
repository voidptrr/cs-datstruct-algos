#include <stdio.h>

#include "ckit/datastruct/binary_heap.h"

static int cmp_int_asc(const void *a, const void *b) {
    int lhs = *(const int *)a;
    int rhs = *(const int *)b;
    return (lhs > rhs) - (lhs < rhs);
}

int main(void) {
    ckit_binary_heap heap;
    int out = 0;
    int value = 3;

    if (ckit_binary_heap_peek(NULL, &out) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_binary_heap_peek(NULL, &out) should return CKIT_ERR_NULL\n");
        return 1;
    }

    if (ckit_binary_heap_init(&heap, sizeof(int), cmp_int_asc, NULL) != CKIT_OK) {
        fprintf(stderr, "ckit_binary_heap_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_binary_heap_peek(&heap, NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_binary_heap_peek(&heap, NULL) should return CKIT_ERR_NULL\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    if (ckit_binary_heap_peek(&heap, &out) != CKIT_ERR_EMPTY) {
        fprintf(stderr, "ckit_binary_heap_peek on empty heap should return CKIT_ERR_EMPTY\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    if (ckit_binary_heap_push(&heap, &value) != CKIT_OK) {
        fprintf(stderr, "ckit_binary_heap_push should return CKIT_OK\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    if (ckit_binary_heap_peek(&heap, &out) != CKIT_OK || out != 3) {
        fprintf(stderr, "ckit_binary_heap_peek should return top element\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    if (ckit_binary_heap_size(&heap) != 1U) {
        fprintf(stderr, "ckit_binary_heap_peek should not change heap size\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    ckit_binary_heap_free(&heap);
    return 0;
}
