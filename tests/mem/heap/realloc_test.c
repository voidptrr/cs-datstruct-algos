#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ckit/mem/allocators/general_heap.h"

int main(void) {
    ckit_heap heap;
    char *ptr;

    if (ckit_heap_init(&heap, 4096U) != CKIT_OK) {
        fprintf(stderr, "ckit_heap_init should return CKIT_OK\n");
        return 1;
    }

    ptr = (char *)ckit_heap_realloc(&heap, NULL, 32U);
    if (ptr == NULL) {
        fprintf(stderr, "ckit_heap_realloc(NULL, size) should allocate\n");
        ckit_heap_free(&heap);
        return 1;
    }

    memcpy(ptr, "hello", 6U);
    ptr = (char *)ckit_heap_realloc(&heap, ptr, 128U);
    if (ptr == NULL) {
        fprintf(stderr, "ckit_heap_realloc should grow allocation when possible\n");
        ckit_heap_free(&heap);
        return 1;
    }

    if (memcmp(ptr, "hello", 6U) != 0) {
        fprintf(stderr, "ckit_heap_realloc should preserve previous bytes\n");
        ckit_heap_free(&heap);
        return 1;
    }

    if (ckit_heap_realloc(&heap, ptr, 0U) != NULL) {
        fprintf(stderr, "ckit_heap_realloc(..., 0) should return NULL\n");
        ckit_heap_free(&heap);
        return 1;
    }

    if (ckit_heap_realloc(NULL, NULL, 64U) != NULL) {
        fprintf(stderr, "ckit_heap_realloc(NULL, ...) should return NULL\n");
        ckit_heap_free(&heap);
        return 1;
    }

    if (ckit_heap_free(&heap) != CKIT_OK) {
        fprintf(stderr, "ckit_heap_free should return CKIT_OK\n");
        return 1;
    }

    return 0;
}
