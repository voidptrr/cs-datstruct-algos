# datastruct.linked_list

## DESCRIPTION

The linked_list module provides a generic singly linked list for fixed-size elements.
It supports insertion at head and tail and removal from head.

## FUNCTIONS

### ckit_linked_list_init

```c
ckit_status ckit_linked_list_init(ckit_linked_list *list, size_t elem_size,
                                  ckit_allocator *allocator);
```

- Parameters: `list`, `elem_size`, `allocator`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `list` is `NULL`; CKIT_ERR_RANGE if `elem_size == 0`.
- Notes: when `allocator` is `NULL`, linked list uses default `ckit_malloc` backing.

### ckit_linked_list_push

```c
ckit_status ckit_linked_list_push(ckit_linked_list *list, const void *element);
```

- Parameters: `list`, `element`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `list` or `element` is `NULL`.

### ckit_linked_list_pushfront

```c
ckit_status ckit_linked_list_pushfront(ckit_linked_list *list, const void *element);
```

- Parameters: `list`, `element`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `list` or `element` is `NULL`.

### ckit_linked_list_popleft

```c
ckit_status ckit_linked_list_popleft(ckit_linked_list *list, void *out);
```

- Parameters: `list`, `out`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `list` or `out` is `NULL`; CKIT_ERR_EMPTY if list is empty.
- Notes: output parameter content is unspecified on failure.

### ckit_linked_list_free

```c
ckit_status ckit_linked_list_free(ckit_linked_list *list);
```

- Parameters: `list`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `list` is `NULL`.

### ckit_linked_list_size

```c
size_t ckit_linked_list_size(const ckit_linked_list *list);
```

- Parameters: `list`
- Returns: current element count.
- Notes: returns `0` when `list` is `NULL`.

### ckit_linked_list_is_empty

```c
bool ckit_linked_list_is_empty(const ckit_linked_list *list);
```

- Parameters: `list`
- Returns: `true` when empty; otherwise `false`.
- Notes: returns `true` when `list` is `NULL`.
