#include <stddef.h>
#include <stdio.h>

#include "vector.h"

static int test_vector_pop_null_vector(void) {
    int out = 0;

    if (vector_pop(NULL, &out) != VECTOR_ERR_NULL) {
        fprintf(stderr, "vector_pop(NULL, &out) should return VECTOR_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_vector_pop_null_out(void) {
    enum vector_status status;
    struct vector v;

    status = vector_init(&v, sizeof(int));
    if (status != VECTOR_OK) {
        fprintf(stderr, "vector_init(&v, ...) should return VECTOR_OK\n");
        return 1;
    }

    status = vector_pop(&v, NULL);
    if (status != VECTOR_ERR_NULL) {
        fprintf(stderr, "vector_pop(&v, NULL) should return VECTOR_ERR_NULL\n");
        vector_free(&v);
        return 1;
    }

    if (vector_free(&v) != VECTOR_OK) {
        fprintf(stderr, "vector_free(&v) should return VECTOR_OK\n");
        return 1;
    }

    return 0;
}

static int test_vector_pop_empty_vector(void) {
    enum vector_status status;
    struct vector v;

    status = vector_init(&v, sizeof(int));
    if (status != VECTOR_OK) {
        fprintf(stderr, "vector_init(&v, ...) should return VECTOR_OK\n");
        return 1;
    }

    {
        int out = 0;
        if (vector_pop(&v, &out) != VECTOR_ERR_EMPTY) {
            fprintf(stderr, "vector_pop on empty vector should return VECTOR_ERR_EMPTY\n");
            vector_free(&v);
            return 1;
        }
    }

    if (vector_size(&v) != 0) {
        fprintf(stderr, "vector_pop on empty vector should not change size\n");
        vector_free(&v);
        return 1;
    }

    if (vector_free(&v) != VECTOR_OK) {
        fprintf(stderr, "vector_free(&v) should return VECTOR_OK\n");
        return 1;
    }

    return 0;
}

static int test_vector_pop_returns_last_value(void) {
    enum vector_status status;
    struct vector v;
    int first = 7;
    int second = 11;
    int popped = 0;

    status = vector_init(&v, sizeof(int));
    if (status != VECTOR_OK) {
        fprintf(stderr, "vector_init(&v, ...) should return VECTOR_OK\n");
        return 1;
    }

    status = vector_push(&v, &first);
    if (status != VECTOR_OK) {
        fprintf(stderr, "first vector_push should return VECTOR_OK\n");
        vector_free(&v);
        return 1;
    }

    status = vector_push(&v, &second);
    if (status != VECTOR_OK) {
        fprintf(stderr, "second vector_push should return VECTOR_OK\n");
        vector_free(&v);
        return 1;
    }

    status = vector_pop(&v, &popped);
    if (status != VECTOR_OK) {
        fprintf(stderr, "vector_pop should return VECTOR_OK\n");
        vector_free(&v);
        return 1;
    }

    if (popped != second) {
        fprintf(stderr, "vector_pop should return last pushed value\n");
        vector_free(&v);
        return 1;
    }

    if (vector_size(&v) != 1) {
        fprintf(stderr, "vector_pop should decrement vector size\n");
        vector_free(&v);
        return 1;
    }

    status = vector_pop(&v, &popped);
    if (status != VECTOR_OK || popped != first) {
        fprintf(stderr, "vector_pop should preserve LIFO order\n");
        vector_free(&v);
        return 1;
    }

    if (vector_size(&v) != 0) {
        fprintf(stderr, "vector should be empty after popping all elements\n");
        vector_free(&v);
        return 1;
    }

    if (vector_free(&v) != VECTOR_OK) {
        fprintf(stderr, "vector_free(&v) should return VECTOR_OK\n");
        return 1;
    }

    return 0;
}

int main(void) {
    if (test_vector_pop_null_vector() != 0) {
        return 1;
    }

    if (test_vector_pop_empty_vector() != 0) {
        return 1;
    }

    if (test_vector_pop_null_out() != 0) {
        return 1;
    }

    if (test_vector_pop_returns_last_value() != 0) {
        return 1;
    }

    return 0;
}
