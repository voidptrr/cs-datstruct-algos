#ifndef CSTD_DATASTRUCT_VECTOR_H
#define CSTD_DATASTRUCT_VECTOR_H

#include <stddef.h>

#include "status.h"

/*
 * Generic contiguous dynamic array storage.
 * +----------------------+----------------------+----------------------+----------------------+
 * | size (size_t)        | elem_size (size_t)   | capacity (size_t)    | buffer (void *)      |
 * +----------------------+----------------------+----------------------+----------------------+
 */
struct cstd_vector {
    size_t size;
    size_t elem_size;
    size_t capacity;
    void *buffer;
};

/* Initialize a vector with element size elem_size. */
enum cstd_status cstd_vector_init(struct cstd_vector *vector, size_t elem_size);

/* Append one element by copying elem_size bytes from element. */
enum cstd_status cstd_vector_push(struct cstd_vector *vector, const void *element);

/* Remove the last element and copy it into out. */
enum cstd_status cstd_vector_pop(struct cstd_vector *vector, void *out);

/* Release owned storage and reset vector to an empty state. */
enum cstd_status cstd_vector_free(struct cstd_vector *vector);

/* Return the number of stored elements. */
size_t cstd_vector_size(const struct cstd_vector *vector);

#endif
