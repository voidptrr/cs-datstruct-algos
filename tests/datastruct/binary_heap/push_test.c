#include <stdio.h>

#include "ckit/datastruct/binary_heap.h"

static int cmp_int_asc(const void *a, const void *b) {
    int lhs = *(const int *)a;
    int rhs = *(const int *)b;
    return (lhs > rhs) - (lhs < rhs);
}

int main(void) {
    ckit_binary_heap heap;
    int value = 5;
    int top = 0;

    if (ckit_binary_heap_push(NULL, &value) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_binary_heap_push(NULL, &value) should return CKIT_ERR_NULL\n");
        return 1;
    }

    if (ckit_binary_heap_init(&heap, sizeof(int), cmp_int_asc, NULL) != CKIT_OK) {
        fprintf(stderr, "ckit_binary_heap_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_binary_heap_push(&heap, NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_binary_heap_push(&heap, NULL) should return CKIT_ERR_NULL\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    int values[] = {5, 2, 8, 1, 7};
    for (size_t i = 0; i < 5; i++) {
        if (ckit_binary_heap_push(&heap, &values[i]) != CKIT_OK) {
            fprintf(stderr, "ckit_binary_heap_push should return CKIT_OK\n");
            ckit_binary_heap_free(&heap);
            return 1;
        }
    }

    if (ckit_binary_heap_size(&heap) != 5U) {
        fprintf(stderr, "heap size should be 5 after pushes\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    if (ckit_binary_heap_peek(&heap, &top) != CKIT_OK || top != 1) {
        fprintf(stderr, "heap top should be minimum element after pushes\n");
        ckit_binary_heap_free(&heap);
        return 1;
    }

    ckit_binary_heap_free(&heap);
    return 0;
}
