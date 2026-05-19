# mem.general_heap

## DESCRIPTION

The heap module provides a general-purpose in-process allocator backed by an
internal contiguous region. It supports allocation, deallocation, and reallocation
using a coalescing free-list strategy.

## FUNCTIONS

### ckit_heap_init

```c
ckit_status ckit_heap_init(ckit_heap *heap, size_t capacity);
```

- Parameters: `heap`, `capacity`
- Returns: `CKIT_OK` on success.
- Errors: `CKIT_ERR_NULL` if `heap` is `NULL`; `CKIT_ERR_RANGE` if `capacity` is too small.

### ckit_heap_free

```c
ckit_status ckit_heap_free(ckit_heap *heap);
```

- Parameters: `heap`
- Returns: `CKIT_OK` on success.
- Errors: `CKIT_ERR_NULL` if `heap` is `NULL`.

### ckit_heap_alloc

```c
void *ckit_heap_alloc(ckit_heap *heap, size_t size);
```

- Parameters: `heap`, `size`
- Returns: allocated pointer, or `NULL` when allocation cannot be satisfied.

### ckit_heap_dealloc

```c
void ckit_heap_dealloc(ckit_heap *heap, void *ptr);
```

- Parameters: `heap`, `ptr`
- Behavior: frees `ptr` if valid; ignores `NULL`.

### ckit_heap_realloc

```c
void *ckit_heap_realloc(ckit_heap *heap, void *ptr, size_t size);
```

- Parameters: `heap`, `ptr`, `size`
- Returns: resized pointer, or `NULL` on failure.
- Notes: `ptr == NULL` behaves like allocation; `size == 0` frees `ptr` and returns `NULL`.

### ckit_heap_capacity

```c
size_t ckit_heap_capacity(const ckit_heap *heap);
```

- Parameters: `heap`
- Returns: total managed bytes, or `0` when `heap` is `NULL`.

### ckit_heap_available

```c
size_t ckit_heap_available(const ckit_heap *heap);
```

- Parameters: `heap`
- Returns: sum of currently free payload bytes, or `0` when `heap` is `NULL`.
