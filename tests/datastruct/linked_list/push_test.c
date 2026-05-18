#include <stddef.h>
#include <stdio.h>

#include "ckit/datastruct/linked_list.h"

static int test_linked_list_push_null_pointers(void) {
    ckit_status status;
    ckit_linked_list list;
    int value = 1;

    status = ckit_linked_list_push(NULL, &value);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_linked_list_push(NULL, &value) should return CKIT_ERR_NULL\n");
        return 1;
    }

    status = ckit_linked_list_init(&list, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init(&list, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_linked_list_push(&list, NULL);
    if (status != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_linked_list_push(&list, NULL) should return CKIT_ERR_NULL\n");
        return 1;
    }

    status = ckit_linked_list_free(&list);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_free(&list) should return CKIT_OK\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_push_single_value(void) {
    ckit_status status;
    ckit_linked_list list;
    int value = 42;

    status = ckit_linked_list_init(&list, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init(&list, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_linked_list_push(&list, &value);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_push(&list, &value) should return CKIT_OK\n");
        return 1;
    }

    if (ckit_linked_list_size(&list) != 1 || list.head == NULL || list.tail == NULL ||
        list.head != list.tail) {
        fprintf(stderr, "ckit_linked_list_push should set head/tail and size for first node\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (*(int *)list.head->data != 42) {
        fprintf(stderr, "ckit_linked_list_push should copy pushed element data\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    status = ckit_linked_list_free(&list);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_free(&list) should return CKIT_OK\n");
        return 1;
    }

    return 0;
}

static int test_linked_list_push_appends_and_copies(void) {
    ckit_status status;
    ckit_linked_list list;
    int first = 7;
    int second = 11;

    status = ckit_linked_list_init(&list, sizeof(int));
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_init(&list, ...) should return CKIT_OK\n");
        return 1;
    }

    status = ckit_linked_list_push(&list, &first);
    if (status != CKIT_OK) {
        fprintf(stderr, "first ckit_linked_list_push should return CKIT_OK\n");
        return 1;
    }

    first = 999;

    status = ckit_linked_list_push(&list, &second);
    if (status != CKIT_OK) {
        fprintf(stderr, "second ckit_linked_list_push should return CKIT_OK\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (ckit_linked_list_size(&list) != 2 || list.head == NULL || list.tail == NULL ||
        list.head == list.tail) {
        fprintf(stderr, "ckit_linked_list_push should append and keep distinct head/tail\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (*(int *)list.head->data != 7 || *(int *)list.tail->data != 11) {
        fprintf(stderr,
                "ckit_linked_list_push should preserve insertion order and copied values\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    if (list.head->next != list.tail || list.tail->next != NULL) {
        fprintf(stderr, "ckit_linked_list_push should link nodes correctly\n");
        ckit_linked_list_free(&list);
        return 1;
    }

    status = ckit_linked_list_free(&list);
    if (status != CKIT_OK) {
        fprintf(stderr, "ckit_linked_list_free(&list) should return CKIT_OK\n");
        return 1;
    }

    return 0;
}

int main(void) {
    if (test_linked_list_push_null_pointers() != 0) {
        return 1;
    }

    if (test_linked_list_push_single_value() != 0) {
        return 1;
    }

    if (test_linked_list_push_appends_and_copies() != 0) {
        return 1;
    }

    return 0;
}
