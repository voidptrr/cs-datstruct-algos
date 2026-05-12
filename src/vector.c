#include <stddef.h>
#include <stdlib.h>

#include "vector.h"

#define DEFAULT_CAPACITY 50

enum vector_status vector_init(struct vector *vector, size_t elem_size) {
    if (vector == NULL) {
        return VECTOR_ERR_NULL;
    }

    void *init_data = malloc(elem_size * DEFAULT_CAPACITY);
    if (init_data == NULL) {
        return VECTOR_ERR_OOM;
    }

    vector->buffer = init_data;
    vector->size = 0;
    vector->elem_size = elem_size;
    vector->capacity = DEFAULT_CAPACITY;

    return VECTOR_OK;
}
