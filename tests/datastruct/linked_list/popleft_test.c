#include <stdio.h>

#include "ckit/datastruct/linked_list.h"

static int test_linked_list_popleft_null_pointers(void) {
    ckit_linked_list list;
    int out = 0;

    if (ckit_linked_list_init(&list, sizeof(int)) != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_linked_list_popleft(NULL, &out) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_linked_list_popleft(NULL, &out) should return CKIT_ERR_NULL\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_popleft(&list, NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_linked_list_popleft(&list, NULL) should return CKIT_ERR_NULL\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    ckit_linked_list_free(&list);
    return 0;
}

static int test_linked_list_popleft_empty(void) {
    ckit_linked_list list;
    int out = 0;

    if (ckit_linked_list_init(&list, sizeof(int)) != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_linked_list_popleft(&list, &out) != CKIT_ERR_EMPTY) {
        fprintf(stderr, "ckit_linked_list_popleft on empty list should return CKIT_ERR_EMPTY\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    ckit_linked_list_free(&list);
    return 0;
}

static int test_linked_list_popleft_fifo_behavior(void) {
    ckit_linked_list list;
    int first = 5;
    int second = 9;
    int out = 0;

    if (ckit_linked_list_init(&list, sizeof(int)) != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_linked_list_push(&list, &first) != CKIT_OK ||
        ckit_linked_list_push(&list, &second) != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_push should return CKIT_OK\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_popleft(&list, &out) != CKIT_OK || out != first) {
        fprintf(stderr, "first ckit_linked_list_popleft should return oldest value\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_popleft(&list, &out) != CKIT_OK || out != second) {
        fprintf(stderr, "second ckit_linked_list_popleft should return second value\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_size(&list) != 0 || list.head != NULL || list.tail != NULL) {
        fprintf(stderr, "ckit_linked_list_popleft should reset head/tail on empty\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    ckit_linked_list_free(&list);
    return 0;
}

int main(void) {
    if (test_linked_list_popleft_null_pointers() != 0) {
        return 1;
    }

    if (test_linked_list_popleft_empty() != 0) {
        return 1;
    }

    if (test_linked_list_popleft_fifo_behavior() != 0) {
        return 1;
    }

    return 0;
}
