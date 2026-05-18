#include <stdint.h>
#include <stdio.h>

#include "ckit/mem/allocators/general_heap.h"

int main(void) {
    ckit_heap heap;
    size_t before;
    size_t after;
    int *a;
    int *b;

    if (ckit_heap_init(&heap, 2048U) != CKIT_OK) {
        fprintf(stderr, "ckit_heap_init should return CKIT_OK\n");
        return 1;
    }

    before = ckit_heap_available(&heap);
    a = (int *)ckit_heap_alloc(&heap, sizeof(int));
    b = (int *)ckit_heap_alloc(&heap, sizeof(int));
    if (a == NULL || b == NULL) {
        fprintf(stderr, "ckit_heap_alloc should return non-NULL for small allocations\n");
        ckit_heap_free(&heap);
        return 1;
    }

    *a = 7;
    *b = 11;
    if (*a != 7 || *b != 11) {
        fprintf(stderr, "heap allocation should be writable\n");
        ckit_heap_free(&heap);
        return 1;
    }

    after = ckit_heap_available(&heap);
    if (after >= before) {
        fprintf(stderr, "available bytes should decrease after allocations\n");
        ckit_heap_free(&heap);
        return 1;
    }

    ckit_heap_dealloc(&heap, a);
    ckit_heap_dealloc(&heap, b);
    if (ckit_heap_available(&heap) <= after) {
        fprintf(stderr, "available bytes should increase after deallocation\n");
        ckit_heap_free(&heap);
        return 1;
    }

    ckit_heap_dealloc(&heap, NULL);
    ckit_heap_dealloc(NULL, b);

    if (ckit_heap_free(&heap) != CKIT_OK) {
        fprintf(stderr, "ckit_heap_free should return CKIT_OK\n");
        return 1;
    }

    return 0;
}
