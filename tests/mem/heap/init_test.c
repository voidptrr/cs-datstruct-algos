#include <stdio.h>

#include "ckit/mem/allocators/general_heap.h"

int main(void) {
    ckit_heap heap;

    if (ckit_heap_init(NULL, 1024U) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_heap_init(NULL, ...) should return CKIT_ERR_NULL\n");
        return 1;
    }

    if (ckit_heap_init(&heap, 8U) != CKIT_ERR_RANGE) {
        fprintf(stderr, "ckit_heap_init(&heap, tiny) should return CKIT_ERR_RANGE\n");
        return 1;
    }

    if (ckit_heap_init(&heap, 1024U) != CKIT_OK) {
        fprintf(stderr, "ckit_heap_init(&heap, ...) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_heap_capacity(&heap) == 0U) {
        fprintf(stderr, "ckit_heap_capacity should be non-zero after init\n");
        ckit_heap_free(&heap);
        return 1;
    }

    if (ckit_heap_available(&heap) == 0U) {
        fprintf(stderr, "ckit_heap_available should be non-zero after init\n");
        ckit_heap_free(&heap);
        return 1;
    }

    if (ckit_heap_free(&heap) != CKIT_OK) {
        fprintf(stderr, "ckit_heap_free should return CKIT_OK\n");
        return 1;
    }

    return 0;
}
