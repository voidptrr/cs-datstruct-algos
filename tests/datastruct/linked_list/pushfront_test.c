#include <stdio.h>

#include "ckit/datastruct/linked_list.h"

static int test_linked_list_pushfront_null_pointers(void) {
    ckit_linked_list list;
    ckit_status status = ckit_linked_list_init(&list, sizeof(int));
    int value = 1;

    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_linked_list_pushfront(NULL, &value) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_linked_list_pushfront(NULL, &value) should return CKIT_ERR_NULL\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_pushfront(&list, NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_linked_list_pushfront(&list, NULL) should return CKIT_ERR_NULL\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    ckit_linked_list_free(&list);
    return 0;
}

static int test_linked_list_pushfront_orders_values(void) {
    ckit_linked_list list;
    int first = 1;
    int second = 2;

    if (ckit_linked_list_init(&list, sizeof(int)) != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_linked_list_pushfront(&list, &first) != CKIT_OK ||
        ckit_linked_list_pushfront(&list, &second) != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_pushfront should return CKIT_OK\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_size(&list) != 2) {
        fprintf(stderr, "ckit_linked_list_pushfront should update size\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (*(int *)list.head->data != 2 || *(int *)list.tail->data != 1) {
        fprintf(stderr, "ckit_linked_list_pushfront should prepend values\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    ckit_linked_list_free(&list);
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
