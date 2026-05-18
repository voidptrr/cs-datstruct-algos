# datastruct.deque

## DESCRIPTION

The deque module provides a generic circular-buffer deque for fixed-size elements.
It supports front and back insertion/removal and read-only peeks on both ends.

## FUNCTIONS

### ckit_deque_init

```c
ckit_status ckit_deque_init(ckit_deque *deque, size_t elem_size);
```

- Parameters: `deque`, `elem_size`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `deque` is `NULL`; CKIT_ERR_RANGE if `elem_size == 0`.

### ckit_deque_push

```c
ckit_status ckit_deque_push(ckit_deque *deque, const void *element);
```

- Parameters: `deque`, `element`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `deque` or `element` is `NULL`.

### ckit_deque_pushfront

```c
ckit_status ckit_deque_pushfront(ckit_deque *deque, const void *element);
```

- Parameters: `deque`, `element`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `deque` or `element` is `NULL`.

### ckit_deque_popleft

```c
ckit_status ckit_deque_popleft(ckit_deque *deque, void *out);
```

- Parameters: `deque`, `out`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `deque` or `out` is `NULL`; CKIT_ERR_EMPTY if deque is empty.
- Notes: output parameter content is unspecified on failure.

### ckit_deque_popback

```c
ckit_status ckit_deque_popback(ckit_deque *deque, void *out);
```

- Parameters: `deque`, `out`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `deque` or `out` is `NULL`; CKIT_ERR_EMPTY if deque is empty.
- Notes: output parameter content is unspecified on failure.

### ckit_deque_peekleft

```c
ckit_status ckit_deque_peekleft(const ckit_deque *deque, void *out);
```

- Parameters: `deque`, `out`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `deque` or `out` is `NULL`; CKIT_ERR_EMPTY if deque is empty.
- Notes: output parameter content is unspecified on failure.

### ckit_deque_peekback

```c
ckit_status ckit_deque_peekback(const ckit_deque *deque, void *out);
```

- Parameters: `deque`, `out`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `deque` or `out` is `NULL`; CKIT_ERR_EMPTY if deque is empty.
- Notes: output parameter content is unspecified on failure.

### ckit_deque_free

```c
ckit_status ckit_deque_free(ckit_deque *deque);
```

- Parameters: `deque`
- Returns: CKIT_OK on success.
- Errors: CKIT_ERR_NULL if `deque` is `NULL`.

### ckit_deque_size

```c
size_t ckit_deque_size(const ckit_deque *deque);
```

- Parameters: `deque`
- Returns: current element count.
- Notes: returns `0` when `deque` is `NULL`.

### ckit_deque_is_empty

```c
bool ckit_deque_is_empty(const ckit_deque *deque);
```

- Parameters: `deque`
- Returns: `true` when empty; otherwise `false`.
- Notes: returns `true` when `deque` is `NULL`.
