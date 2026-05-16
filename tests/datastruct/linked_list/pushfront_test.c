#include <stdio.h>

#include "cstd/datastruct/linked_list.h"

static int test_linked_list_pushfront_null_pointers(void) {
    cstd_linked_list list;
    cstd_status status = cstd_linked_list_init(&list, sizeof(int));
    int value = 1;

    if (status != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_init should return CSTD_OK\n");
        return 1;
    }

    if (cstd_linked_list_pushfront(NULL, &value) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_linked_list_pushfront(NULL, &value) should return CSTD_ERR_NULL\n");
        cstd_linked_list_free(&list);
        return 1;
    }

    if (cstd_linked_list_pushfront(&list, NULL) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_linked_list_pushfront(&list, NULL) should return CSTD_ERR_NULL\n");
        cstd_linked_list_free(&list);
        return 1;
    }

    cstd_linked_list_free(&list);
    return 0;
}

static int test_linked_list_pushfront_orders_values(void) {
    cstd_linked_list list;
    int first = 1;
    int second = 2;

    if (cstd_linked_list_init(&list, sizeof(int)) != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_init should return CSTD_OK\n");
        return 1;
    }

    if (cstd_linked_list_pushfront(&list, &first) != CSTD_OK ||
        cstd_linked_list_pushfront(&list, &second) != CSTD_OK) {
        fprintf(stderr, "cstd_linked_list_pushfront should return CSTD_OK\n");
        cstd_linked_list_free(&list);
        return 1;
    }

    if (cstd_linked_list_size(&list) != 2) {
        fprintf(stderr, "cstd_linked_list_pushfront should update size\n");
        cstd_linked_list_free(&list);
        return 1;
    }

    if (*(int *)list.head->data != 2 || *(int *)list.tail->data != 1) {
        fprintf(stderr, "cstd_linked_list_pushfront should prepend values\n");
        cstd_linked_list_free(&list);
        return 1;
    }

    cstd_linked_list_free(&list);
    return 0;
}

int main(void) {
    if (test_linked_list_pushfront_null_pointers() != 0) {
        return 1;
    }

    if (test_linked_list_pushfront_orders_values() != 0) {
        return 1;
    }

    return 0;
}
