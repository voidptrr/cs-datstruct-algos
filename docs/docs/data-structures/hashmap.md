# cstd.datastruct.hashmap

## DESCRIPTION

The hashmap module provides fixed-size key/value mapping with separate chaining for collisions.
Hashing uses an internal FNV-1a function; key equality is provided by a caller callback.

## FUNCTIONS

### cstd_hashmap_init

```c
cstd_status cstd_hashmap_init(cstd_hashmap *map,
                              size_t key_size,
                              size_t value_size,
                              cstd_hashmap_key_eq_fn key_eq);
```

- Parameters: `map`, `key_size`, `value_size`, `key_eq`
- Returns: `CSTD_OK` on success.
- Errors: `CSTD_ERR_NULL` if `map` or `key_eq` is `NULL`; `CSTD_ERR_RANGE` if `key_size == 0` or `value_size == 0`.

### cstd_hashmap_put

```c
cstd_status cstd_hashmap_put(cstd_hashmap *map, const void *key, const void *value);
```

- Parameters: `map`, `key`, `value`
- Returns: `CSTD_OK` on success.
- Errors: `CSTD_ERR_NULL` if `map`, `key`, or `value` is `NULL`.

### cstd_hashmap_get

```c
cstd_status cstd_hashmap_get(const cstd_hashmap *map, const void *key, void *out_value);
```

- Parameters: `map`, `key`, `out_value`
- Returns: `CSTD_OK` on success.
- Errors: `CSTD_ERR_NULL` if `map`, `key`, or `out_value` is `NULL`; `CSTD_ERR_NOT_FOUND` if key is missing.
- Notes: output parameter content is unspecified on failure.

### cstd_hashmap_remove

```c
cstd_status cstd_hashmap_remove(cstd_hashmap *map, const void *key);
```

- Parameters: `map`, `key`
- Returns: `CSTD_OK` on success.
- Errors: `CSTD_ERR_NULL` if `map` or `key` is `NULL`; `CSTD_ERR_NOT_FOUND` if key is missing.

### cstd_hashmap_free

```c
cstd_status cstd_hashmap_free(cstd_hashmap *map);
```

- Parameters: `map`
- Returns: `CSTD_OK` on success.
- Errors: `CSTD_ERR_NULL` if `map` is `NULL`.

### cstd_hashmap_size

```c
size_t cstd_hashmap_size(const cstd_hashmap *map);
```

- Parameters: `map`
- Returns: current entry count.
- Notes: returns `0` when `map` is `NULL`.

### cstd_hashmap_is_empty

```c
bool cstd_hashmap_is_empty(const cstd_hashmap *map);
```

- Parameters: `map`
- Returns: `true` when empty; otherwise `false`.
- Notes: returns `true` when `map` is `NULL`.

## EXAMPLE

```c
#include <cstd/compare.h>
#include <cstd/datastruct/hashmap.h>
#include <cstd/status.h>
#include <stdint.h>

int main(void) {
    cstd_hashmap map;
    uint64_t key = 42U;
    uint64_t value = 9001U;
    uint64_t out = 0U;

    if (cstd_hashmap_init(&map, sizeof(uint64_t), sizeof(uint64_t), cstd_eq_u64) != CSTD_OK) {
        return 1;
    }
    if (cstd_hashmap_put(&map, &key, &value) != CSTD_OK) {
        cstd_hashmap_free(&map);
        return 1;
    }
    if (cstd_hashmap_get(&map, &key, &out) != CSTD_OK) {
        cstd_hashmap_free(&map);
        return 1;
    }
    if (cstd_hashmap_remove(&map, &key) != CSTD_OK) {
        cstd_hashmap_free(&map);
        return 1;
    }

    cstd_hashmap_free(&map);
    return 0;
}
```

## SEE ALSO

`cstd.status`, `cstd.compare`, `cstd.datastruct.benchmarks`
