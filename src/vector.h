#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

enum vector_status { VECTOR_OK, VECTOR_ERR_OOM, VECTOR_ERR_NULL, VECTOR_ERR_EMPTY };

/*
 * Generic contiguous dynamic array storage.
 * +----------------------+----------------------+----------------------+----------------------+
 * | size (size_t)        | elem_size (size_t)   | capacity (size_t)    | buffer (void *)      |
 * +----------------------+----------------------+----------------------+----------------------+
 */
struct vector {
    size_t size;
    size_t elem_size;
    size_t capacity;
    void *buffer;
};

/*
 * Initialize a vector with element size elem_size.
 * Returns VECTOR_OK on success, VECTOR_ERR_NULL when vector is NULL,
 * or VECTOR_ERR_OOM when allocation fails.
 */
enum vector_status vector_init(struct vector *vector, size_t elem_size);

/*
 * Append one element by copying elem_size bytes from element.
 * Returns VECTOR_OK, VECTOR_ERR_NULL for invalid pointers,
 * or VECTOR_ERR_OOM when growth allocation fails.
 */
enum vector_status vector_push(struct vector *vector, const void *element);

/*
 * Remove the last element and copy it into out.
 * Returns VECTOR_OK, VECTOR_ERR_NULL for invalid pointers,
 * or VECTOR_ERR_EMPTY when vector has no elements.
 */
enum vector_status vector_pop(struct vector *vector, void *out);

/*
 * Release owned storage and reset vector to an empty state.
 * Returns VECTOR_OK, or VECTOR_ERR_NULL when vector is NULL.
 */
enum vector_status vector_free(struct vector *vector);

/*
 * Return the number of stored elements.
 * Returns 0 when vector is NULL.
 */
size_t vector_size(struct vector *vector);

#endif
