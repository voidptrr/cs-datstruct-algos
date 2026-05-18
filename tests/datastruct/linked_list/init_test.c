#include <stddef.h>
#include <stdio.h>

#include "ckit/datastruct/linked_list.h"

static int test_linked_list_init_null_pointer(void) {
    ckit_status status;

    status = ckit_linked_list_init(NULL, sizeof(int));
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_linked_list_init(NULL, ...) should return CKIT_ERR_NULL\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_init_valid_pointer(void) {
    ckit_status status;
    ckit_linked_list list;

    status = ckit_linked_list_init(&list, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init(&list, ...) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_linked_list_size(&list) != 0 || list.elem_size != sizeof(int) || list.head != NULL ||
        list.tail != NULL) {
        fprintf(stderr, "ckit_linked_list_init(&list, ...) returned invalid list state\n");
        return 1;
    }

    status = ckit_linked_list_free(&list);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_free(&list) should return CKIT_OK\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_init_zero_elem_size(void) {
    ckit_linked_list list;
    ckit_status status = ckit_linked_list_init(&list, 0);

    if (status != CKIT_ERR_RANGE) {
        fprintf(stderr, "ckit_linked_list_init(&list, 0) should return CKIT_ERR_RANGE\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_is_empty(void) {
    ckit_linked_list list;
    int value = 1;

    if (ckit_linked_list_is_empty(NULL) != true) {
        fprintf(stderr, "ckit_linked_list_is_empty(NULL) should return true\n");
        return 1;
    }

    if (ckit_linked_list_init(&list, sizeof(int)) != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init(&list, ...) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_linked_list_is_empty(&list) != true) {
        fprintf(stderr, "ckit_linked_list_is_empty(&list) should return true for empty list\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_push(&list, &value) != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_push(&list, &value) should return CKIT_OK\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_is_empty(&list) != false) {
        fprintf(stderr, "ckit_linked_list_is_empty(&list) should return false after push\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    ckit_linked_list_free(&list);
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
