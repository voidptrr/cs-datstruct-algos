#include <stddef.h>
#include <stdio.h>

#include "cstd/datastruct/linked_list.h"

static int test_linked_list_free_null_pointer(void) {
    cstd_status status;

    status = cstd_linked_list_free(NULL);
    if (status != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_linked_list_free(NULL) should return CSTD_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_free_empty_list(void) {
    cstd_status status;
    cstd_linked_list list;

    status = cstd_linked_list_init(&list, sizeof(int));
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_init(&list, ...) should return CSTD_OK\n");
        return 1;
    }

    status = cstd_linked_list_free(&list);
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_free(&list) on empty list should return CSTD_OK\n");
        return 1;
    }

    if (list.head != NULL || list.tail != NULL || cstd_linked_list_size(&list) != 0) {
        fprintf(stderr, "cstd_linked_list_free(&list) should keep empty state\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_free_populated_list(void) {
    cstd_status status;
    cstd_linked_list list;
    int values[] = {1, 2, 3};

    status = cstd_linked_list_init(&list, sizeof(int));
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_init(&list, ...) should return CSTD_OK\n");
        return 1;
    }

    for (size_t i = 0; i < 3; i++) {
        status = cstd_linked_list_push(&list, &values[i]);
        if (status != CSTD_OK) {
            fprintf(stderr, "cstd_linked_list_push should succeed before free checks\n");
            cstd_linked_list_free(&list);
            return 1;
        }
    }

    status = cstd_linked_list_free(&list);
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_free(&list) should return CSTD_OK\n");
        return 1;
    }

    if (list.head != NULL || list.tail != NULL || cstd_linked_list_size(&list) != 0) {
        fprintf(stderr, "cstd_linked_list_free(&list) should reset list state\n");
        return 1;
    }

    status = cstd_linked_list_free(&list);
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_free(&list) should be idempotent\n");
        return 1;
    }

    return 0;
}

int main(void) {
    if (test_linked_list_free_null_pointer() != 0) {
        return 1;
    }

    if (test_linked_list_free_empty_list() != 0) {
        return 1;
    }

    if (test_linked_list_free_populated_list() != 0) {
        return 1;
    }

    return 0;
}
