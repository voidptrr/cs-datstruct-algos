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

    if (ckit_binary_heap_pop(NULL, &out) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_binary_heap_pop(NULL, &out) should return CKIT_ERR_NULL\n");
        return 1;
    }

    if (ckit_binary_heap_init(&heap, sizeof(int), cmp_int_asc) != CKIT_OK) {
        fprintf(stderr, "ckit_binary_heap_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_binary_heap_pop(&heap, NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_binary_heap_pop(&heap, NULL) should return CKIT_ERR_NULL\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    if (ckit_binary_heap_pop(&heap, &out) != CKIT_ERR_EMPTY) {
        fprintf(stderr, "ckit_binary_heap_pop on empty heap should return CKIT_ERR_EMPTY\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    int values[] = {9, 4, 6, 1, 7, 2};
    for (size_t i = 0; i < 6; i++) {
        if (ckit_binary_heap_push(&heap, &values[i]) != CKIT_OK) {
            fprintf(stderr, "ckit_binary_heap_push should return CKIT_OK\n");
            ckit_binary_heap_free(&heap);
            return 1;
        }
    }

    int expected[] = {1, 2, 4, 6, 7, 9};
    for (size_t i = 0; i < 6; i++) {
        if (ckit_binary_heap_pop(&heap, &out) != CKIT_OK || out != expected[i]) {
            fprintf(stderr, "ckit_binary_heap_pop should return values in comparator order\n");
            ckit_binary_heap_free(&heap);
            return 1;
        }
    }

    if (!ckit_binary_heap_is_empty(&heap)) {
        fprintf(stderr, "heap should be empty after popping all elements\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    ckit_binary_heap_free(&heap);
    return 0;
}
