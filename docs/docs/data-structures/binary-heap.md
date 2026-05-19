# datastruct.binary_heap

## DESCRIPTION

The binary_heap module provides a generic binary heap backed by a contiguous array (`root`).
Heap ordering is defined by a user-supplied comparator function.

## FUNCTIONS

### ckit_binary_heap_init

```c
ckit_status ckit_binary_heap_init(ckit_binary_heap *heap,
                                  size_t elem_size,
                                  ckit_heap_cmp_fn cmp,
                                  ckit_allocator *allocator);
```

- Parameters: `heap`, `elem_size`, `cmp`, `allocator`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `heap` or `cmp` is `NULL`; CKIT_ERR_RANGE if `elem_size == 0`.
- Notes: when `allocator` is `NULL`, binary heap root storage uses default allocator backing.

### ckit_binary_heap_push

```c
ckit_status ckit_binary_heap_push(ckit_binary_heap *heap, const void *element);
```

- Parameters: `heap`, `element`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `heap` or `element` is `NULL`.

### ckit_binary_heap_pop

```c
ckit_status ckit_binary_heap_pop(ckit_binary_heap *heap, void *out);
```

- Parameters: `heap`, `out`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `heap` or `out` is `NULL`; CKIT_ERR_EMPTY if heap is empty.
- Notes: output parameter content is unspecified on failure.

### ckit_binary_heap_peek

```c
ckit_status ckit_binary_heap_peek(const ckit_binary_heap *heap, void *out);
```

- Parameters: `heap`, `out`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `heap` or `out` is `NULL`; CKIT_ERR_EMPTY if heap is empty.
- Notes: output parameter content is unspecified on failure.

### ckit_binary_heap_free

```c
ckit_status ckit_binary_heap_free(ckit_binary_heap *heap);
```

- Parameters: `heap`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `heap` is `NULL`.

### ckit_binary_heap_size

```c
size_t ckit_binary_heap_size(const ckit_binary_heap *heap);
```

- Parameters: `heap`
- Returns: current element count.
- Notes: returns `0` when `heap` is `NULL`.

### ckit_binary_heap_is_empty

```c
bool ckit_binary_heap_is_empty(const ckit_binary_heap *heap);
```

- Parameters: `heap`
- Returns: `true` when empty; otherwise `false`.
- Notes: returns `true` when `heap` is `NULL`.
