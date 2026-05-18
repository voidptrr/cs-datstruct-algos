# compare

Shared equality and ordering callbacks for containers.

## Equality helpers

### ckit_eq_bytes

```c
bool ckit_eq_bytes(const void *lhs, const void *rhs, size_t size);
```

- Parameters: `lhs`, `rhs`, `size`
- Returns: `true` when byte regions are equal.

### ckit_eq_cstr

```c
bool ckit_eq_cstr(const void *lhs, const void *rhs, size_t size);
```

- Parameters: `lhs`, `rhs`, `size`
- Returns: `true` when null-terminated strings are equal.
- Notes: `size` is ignored.

### ckit_eq_i32 / ckit_eq_i64 / ckit_eq_u32 / ckit_eq_u64

```c
bool ckit_eq_i32(const void *lhs, const void *rhs, size_t size);
bool ckit_eq_i64(const void *lhs, const void *rhs, size_t size);
bool ckit_eq_u32(const void *lhs, const void *rhs, size_t size);
bool ckit_eq_u64(const void *lhs, const void *rhs, size_t size);
```

- Parameters: `lhs`, `rhs`, `size`
- Returns: `true` when scalar values are equal.
- Notes: `size` is ignored.

## Ordering helpers

### ckit_cmp_i32 / ckit_cmp_i64 / ckit_cmp_u32 / ckit_cmp_u64

```c
int ckit_cmp_i32(const void *lhs, const void *rhs);
int ckit_cmp_i64(const void *lhs, const void *rhs);
int ckit_cmp_u32(const void *lhs, const void *rhs);
int ckit_cmp_u64(const void *lhs, const void *rhs);
```

- Parameters: `lhs`, `rhs`
- Returns: negative when `lhs < rhs`, zero when equal, positive when `lhs > rhs`.
