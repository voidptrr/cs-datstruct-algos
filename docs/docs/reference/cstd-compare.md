# cstd.compare

`cstd.compare` provides shared equality and ordering callbacks for containers.

## Equality helpers

### cstd_eq_bytes

```c
bool cstd_eq_bytes(const void *lhs, const void *rhs, size_t size);
```

- Parameters: `lhs`, `rhs`, `size`
- Returns: `true` when byte regions are equal.

### cstd_eq_cstr

```c
bool cstd_eq_cstr(const void *lhs, const void *rhs, size_t size);
```

- Parameters: `lhs`, `rhs`, `size`
- Returns: `true` when null-terminated strings are equal.
- Notes: `size` is ignored.

### cstd_eq_i32 / cstd_eq_i64 / cstd_eq_u32 / cstd_eq_u64

```c
bool cstd_eq_i32(const void *lhs, const void *rhs, size_t size);
bool cstd_eq_i64(const void *lhs, const void *rhs, size_t size);
bool cstd_eq_u32(const void *lhs, const void *rhs, size_t size);
bool cstd_eq_u64(const void *lhs, const void *rhs, size_t size);
```

- Parameters: `lhs`, `rhs`, `size`
- Returns: `true` when scalar values are equal.
- Notes: `size` is ignored.

## Ordering helpers

### cstd_cmp_i32 / cstd_cmp_i64 / cstd_cmp_u32 / cstd_cmp_u64

```c
int cstd_cmp_i32(const void *lhs, const void *rhs);
int cstd_cmp_i64(const void *lhs, const void *rhs);
int cstd_cmp_u32(const void *lhs, const void *rhs);
int cstd_cmp_u64(const void *lhs, const void *rhs);
```

- Parameters: `lhs`, `rhs`
- Returns: negative when `lhs < rhs`, zero when equal, positive when `lhs > rhs`.

## SEE ALSO

`cstd.datastruct.binary_heap`, `cstd.datastruct.hashmap`
