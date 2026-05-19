#include <stdlib.h>
#include <string.h>

#include "ckit/datastruct/linked_list.h"
#include "ckit/mem/allocators/allocator.h"

static void *ckit_linked_list_alloc(const ckit_linked_list *list, size_t size) {
    if (list->allocator == NULL || list->allocator->alloc == NULL) {
        return ckit_malloc(size);
    }
    return list->allocator->alloc(list->allocator->ctx, size);
}

static void ckit_linked_list_dealloc(const ckit_linked_list *list, void *ptr) {
    if (list->allocator == NULL || list->allocator->dealloc == NULL) {
        free(ptr);
        return;
    }
    list->allocator->dealloc(list->allocator->ctx, ptr);
}

ckit_status ckit_linked_list_init(ckit_linked_list *list, size_t elem_size,
                                  ckit_allocator *allocator) {
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
    list->allocator = allocator;

    return CKIT_OK;
}

ckit_status ckit_linked_list_push(ckit_linked_list *list, const void *element) {
    if (list == NULL || element == NULL) {
        return CKIT_ERR_NULL;
    }

    ckit_linked_list_node *new_node = ckit_linked_list_alloc(list, sizeof(ckit_linked_list_node));
    if (new_node == NULL) {
        return CKIT_ERR_RANGE;
    }

    new_node->data = ckit_linked_list_alloc(list, list->elem_size);
    if (new_node->data == NULL) {
        ckit_linked_list_dealloc(list, new_node);
        return CKIT_ERR_RANGE;
    }

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

    ckit_linked_list_node *new_node = ckit_linked_list_alloc(list, sizeof(ckit_linked_list_node));
    if (new_node == NULL) {
        return CKIT_ERR_RANGE;
    }

    new_node->data = ckit_linked_list_alloc(list, list->elem_size);
    if (new_node->data == NULL) {
        ckit_linked_list_dealloc(list, new_node);
        return CKIT_ERR_RANGE;
    }

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

    ckit_linked_list_dealloc(list, old_head->data);
    ckit_linked_list_dealloc(list, old_head);
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
        ckit_linked_list_dealloc(list, curr->data);
        ckit_linked_list_dealloc(list, curr);
        curr = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->allocator = NULL;

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
