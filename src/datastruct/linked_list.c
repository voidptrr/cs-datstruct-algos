#include <stdlib.h>
#include <string.h>

#include "ckit/datastruct/linked_list.h"
#include "ckit/mem/allocators/allocator.h"

ckit_status ckit_linked_list_init(ckit_linked_list *list, size_t elem_size) {
    if (list == NULL) {
        return CKIT_ERR_NULL;
    }

    if (elem_size == 0) {
        return CKIT_ERR_RANGE;
    }

    list->size = 0;
    list->elem_size = elem_size;
    list->head = NULL;
    list->tail = NULL;

    return CKIT_OK;
}

ckit_status ckit_linked_list_push(ckit_linked_list *list, const void *element) {
    if (list == NULL || element == NULL) {
        return CKIT_ERR_NULL;
    }

    ckit_linked_list_node *new_node = ckit_malloc(sizeof(ckit_linked_list_node));

    new_node->data = ckit_malloc(list->elem_size);

    memcpy(new_node->data, element, list->elem_size);
    new_node->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }

    list->tail = new_node;
    list->size += 1;

    return CKIT_OK;
}

ckit_status ckit_linked_list_pushfront(ckit_linked_list *list, const void *element) {
    if (list == NULL || element == NULL) {
        return CKIT_ERR_NULL;
    }

    ckit_linked_list_node *new_node = ckit_malloc(sizeof(ckit_linked_list_node));

    new_node->data = ckit_malloc(list->elem_size);

    memcpy(new_node->data, element, list->elem_size);
    new_node->next = list->head;
    list->head = new_node;

    if (list->tail == NULL) {
        list->tail = new_node;
    }

    list->size += 1;
    return CKIT_OK;
}

ckit_status ckit_linked_list_popleft(ckit_linked_list *list, void *out) {
    if (list == NULL || out == NULL) {
        return CKIT_ERR_NULL;
    }

    if (list->head == NULL) {
        return CKIT_ERR_EMPTY;
    }

    ckit_linked_list_node *old_head = list->head;
    memcpy(out, old_head->data, list->elem_size);
    list->head = old_head->next;

    if (list->head == NULL) {
        list->tail = NULL;
    }

    free(old_head->data);
    free(old_head);
    list->size -= 1;

    return CKIT_OK;
}

ckit_status ckit_linked_list_free(ckit_linked_list *list) {
    if (list == NULL) {
        return CKIT_ERR_NULL;
    }

    ckit_linked_list_node *curr = list->head;
    while (curr != NULL) {
        ckit_linked_list_node *next = curr->next;
        free(curr->data);
        free(curr);
        curr = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return CKIT_OK;
}

size_t ckit_linked_list_size(const ckit_linked_list *list) {
    if (list == NULL) {
        return 0;
    }

    return list->size;
}

bool ckit_linked_list_is_empty(const ckit_linked_list *list) {
    return ckit_linked_list_size(list) == 0;
}
