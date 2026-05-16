#include <stddef.h>
#include <stdio.h>

#include "cstd/datastruct/linked_list.h"

static int test_linked_list_init_null_pointer(void) {
    cstd_status status;

    status = cstd_linked_list_init(NULL, sizeof(int));
    if (status != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_linked_list_init(NULL, ...) should return CSTD_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_init_valid_pointer(void) {
    cstd_status status;
    cstd_linked_list list;

    status = cstd_linked_list_init(&list, sizeof(int));
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_init(&list, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_linked_list_size(&list) != 0 || list.elem_size != sizeof(int) || list.head != NULL ||
        list.tail != NULL) {
        fprintf(stderr, "cstd_linked_list_init(&list, ...) returned invalid list state\n");
        return 1;
    }

    status = cstd_linked_list_free(&list);
    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_free(&list) should return CSTD_OK\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_init_zero_elem_size(void) {
    cstd_linked_list list;
    cstd_status status = cstd_linked_list_init(&list, 0);

    if (status != CSTD_ERR_RANGE) {
        fprintf(stderr, "cstd_linked_list_init(&list, 0) should return CSTD_ERR_RANGE\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_is_empty(void) {
    cstd_linked_list list;
    int value = 1;

    if (cstd_linked_list_is_empty(NULL) != true) {
        fprintf(stderr, "cstd_linked_list_is_empty(NULL) should return true\n");
        return 1;
    }

    if (cstd_linked_list_init(&list, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_init(&list, ...) should return CSTD_OK\n");
        return 1;
    }

    if (cstd_linked_list_is_empty(&list) != true) {
        fprintf(stderr, "cstd_linked_list_is_empty(&list) should return true for empty list\n");
        cstd_linked_list_free(&list);
        return 1;
    }

    if (cstd_linked_list_push(&list, &value) != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_push(&list, &value) should return CSTD_OK\n");
        cstd_linked_list_free(&list);
        return 1;
    }

    if (cstd_linked_list_is_empty(&list) != false) {
        fprintf(stderr, "cstd_linked_list_is_empty(&list) should return false after push\n");
        cstd_linked_list_free(&list);
        return 1;
    }

    cstd_linked_list_free(&list);
    return 0;
}

int main(void) {
    if (test_linked_list_init_null_pointer() != 0) {
        return 1;
    }

    if (test_linked_list_init_valid_pointer() != 0) {
        return 1;
    }

    if (test_linked_list_init_zero_elem_size() != 0) {
        return 1;
    }

    if (test_linked_list_is_empty() != 0) {
        return 1;
    }

    return 0;
}
