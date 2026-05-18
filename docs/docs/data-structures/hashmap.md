# datastruct.hashmap

## DESCRIPTION

The hashmap module provides fixed-size key/value mapping with separate chaining for collisions.
Hashing uses an internal FNV-1a function; key equality is provided by a caller callback.

## FUNCTIONS

### ckit_hashmap_init

```c
ckit_status ckit_hashmap_init(ckit_hashmap *map,
                              size_t key_size,
                              size_t value_size,
                              ckit_hashmap_key_eq_fn key_eq);
```

- Parameters: `map`, `key_size`, `value_size`, `key_eq`
- Returns: `CKIT_OK` on success.
- Errors: `CKIT_ERR_NULL` if `map` or `key_eq` is `NULL`; `CKIT_ERR_RANGE` if `key_size == 0` or `value_size == 0`.

### ckit_hashmap_put

```c
ckit_status ckit_hashmap_put(ckit_hashmap *map, const void *key, const void *value);
```

- Parameters: `map`, `key`, `value`
- Returns: `CKIT_OK` on success.
- Errors: `CKIT_ERR_NULL` if `map`, `key`, or `value` is `NULL`.

### ckit_hashmap_get

```c
ckit_status ckit_hashmap_get(const ckit_hashmap *map, const void *key, void *out_value);
```

- Parameters: `map`, `key`, `out_value`
- Returns: `CKIT_OK` on success.
- Errors: `CKIT_ERR_NULL` if `map`, `key`, or `out_value` is `NULL`; `CKIT_ERR_NOT_FOUND` if key is missing.
- Notes: output parameter content is unspecified on failure.

### ckit_hashmap_remove

```c
ckit_status ckit_hashmap_remove(ckit_hashmap *map, const void *key);
```

- Parameters: `map`, `key`
- Returns: `CKIT_OK` on success.
- Errors: `CKIT_ERR_NULL` if `map` or `key` is `NULL`; `CKIT_ERR_NOT_FOUND` if key is missing.

### ckit_hashmap_free

```c
ckit_status ckit_hashmap_free(ckit_hashmap *map);
```

- Parameters: `map`
- Returns: `CKIT_OK` on success.
- Errors: `CKIT_ERR_NULL` if `map` is `NULL`.

### ckit_hashmap_size

```c
size_t ckit_hashmap_size(const ckit_hashmap *map);
```

- Parameters: `map`
- Returns: current entry count.
- Notes: returns `0` when `map` is `NULL`.

### ckit_hashmap_is_empty

```c
bool ckit_hashmap_is_empty(const ckit_hashmap *map);
```

- Parameters: `map`
- Returns: `true` when empty; otherwise `false`.
- Notes: returns `true` when `map` is `NULL`.

## EXAMPLE

```c
#include <ckit/compare.h>
#include <ckit/datastruct/hashmap.h>
#include <ckit/status.h>
#include <stdint.h>

int main(void) {
    ckit_hashmap map;
    uint64_t key = 42U;
    uint64_t value = 9001U;
    uint64_t out = 0U;

    if (ckit_hashmap_init(&map, sizeof(uint64_t), sizeof(uint64_t), ckit_eq_u64) != CKIT_OK) {
        return 1;
    }
    if (ckit_hashmap_put(&map, &key, &value) != CKIT_OK) {
        ckit_hashmap_free(&map);
        return 1;
    }
    if (ckit_hashmap_get(&map, &key, &out) != CKIT_OK) {
        ckit_hashmap_free(&map);
        return 1;
    }
    if (ckit_hashmap_remove(&map, &key) != CKIT_OK) {
        ckit_hashmap_free(&map);
        return 1;
    }

    ckit_hashmap_free(&map);
    return 0;
}
```
