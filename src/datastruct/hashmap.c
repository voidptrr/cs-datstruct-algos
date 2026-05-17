#include <string.h>
#include <stdlib.h>

#include "cstd/datastruct/hashmap.h"
#include "crypto/fnv1a.h"
#include "cstd/mem/allocator.h"

#define CSTD_HASHMAP_DEFAULT_CAPACITY 16U
#define CSTD_HASHMAP_MAX_LOAD_FACTOR_NUM 3U
#define CSTD_HASHMAP_MAX_LOAD_FACTOR_DEN 4U

static size_t cstd_hashmap_bucket_index(const cstd_hashmap *map, const void *key) {
    size_t hash = cstd_internal_fnv1a_hash(key, map->key_size);
    return hash % map->capacity;
}

static bool cstd_hashmap_should_grow(const cstd_hashmap *map) {
    return (map->size + 1U) * CSTD_HASHMAP_MAX_LOAD_FACTOR_DEN >
           map->capacity * CSTD_HASHMAP_MAX_LOAD_FACTOR_NUM;
}

static void cstd_hashmap_rehash(cstd_hashmap *map, size_t new_capacity) {
    cstd_hashmap_entry **new_buckets = cstd_malloc(sizeof(*new_buckets) * new_capacity);
    memset(new_buckets, 0, sizeof(*new_buckets) * new_capacity);

    for (size_t i = 0U; i < map->capacity; i++) {
        cstd_hashmap_entry *curr = map->buckets[i];
        while (curr != NULL) {
            cstd_hashmap_entry *next = curr->next;
            size_t hash = cstd_internal_fnv1a_hash(curr->key, map->key_size);
            size_t bucket = hash % new_capacity;

            curr->next = new_buckets[bucket];
            new_buckets[bucket] = curr;
            curr = next;
        }
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;
}

cstd_status cstd_hashmap_init(cstd_hashmap *map, size_t key_size, size_t value_size,
                              cstd_hashmap_key_eq_fn key_eq) {
    if (map == NULL || key_eq == NULL) {
        return CSTD_ERR_NULL;
    }
    if (key_size == 0U || value_size == 0U) {
        return CSTD_ERR_RANGE;
    }

    map->buckets = cstd_malloc(sizeof(*map->buckets) * CSTD_HASHMAP_DEFAULT_CAPACITY);
    memset(map->buckets, 0, sizeof(*map->buckets) * CSTD_HASHMAP_DEFAULT_CAPACITY);

    map->size = 0U;
    map->key_size = key_size;
    map->value_size = value_size;
    map->capacity = CSTD_HASHMAP_DEFAULT_CAPACITY;
    map->key_eq = key_eq;

    return CSTD_OK;
}

cstd_status cstd_hashmap_put(cstd_hashmap *map, const void *key, const void *value) {
    if (map == NULL || key == NULL || value == NULL) {
        return CSTD_ERR_NULL;
    }

    size_t bucket = cstd_hashmap_bucket_index(map, key);
    cstd_hashmap_entry *curr = map->buckets[bucket];

    while (curr != NULL) {
        if (map->key_eq(curr->key, key, map->key_size)) {
            memcpy(curr->value, value, map->value_size);
            return CSTD_OK;
        }
        curr = curr->next;
    }

    if (cstd_hashmap_should_grow(map)) {
        cstd_hashmap_rehash(map, map->capacity * 2U);
        bucket = cstd_hashmap_bucket_index(map, key);
    }

    cstd_hashmap_entry *entry = cstd_malloc(sizeof(*entry));
    entry->key = cstd_malloc(map->key_size);
    entry->value = cstd_malloc(map->value_size);

    memcpy(entry->key, key, map->key_size);
    memcpy(entry->value, value, map->value_size);

    entry->next = map->buckets[bucket];
    map->buckets[bucket] = entry;
    map->size += 1U;

    return CSTD_OK;
}

cstd_status cstd_hashmap_get(const cstd_hashmap *map, const void *key, void *out_value) {
    if (map == NULL || key == NULL || out_value == NULL) {
        return CSTD_ERR_NULL;
    }

    size_t bucket = cstd_hashmap_bucket_index(map, key);
    cstd_hashmap_entry *curr = map->buckets[bucket];

    while (curr != NULL) {
        if (map->key_eq(curr->key, key, map->key_size)) {
            memcpy(out_value, curr->value, map->value_size);
            return CSTD_OK;
        }
        curr = curr->next;
    }

    return CSTD_ERR_NOT_FOUND;
}

cstd_status cstd_hashmap_remove(cstd_hashmap *map, const void *key) {
    if (map == NULL || key == NULL) {
        return CSTD_ERR_NULL;
    }

    size_t bucket = cstd_hashmap_bucket_index(map, key);
    cstd_hashmap_entry *prev = NULL;
    cstd_hashmap_entry *curr = map->buckets[bucket];

    while (curr != NULL) {
        if (map->key_eq(curr->key, key, map->key_size)) {
            if (prev == NULL) {
                map->buckets[bucket] = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr->key);
            free(curr->value);
            free(curr);
            map->size -= 1U;
            return CSTD_OK;
        }

        prev = curr;
        curr = curr->next;
    }

    return CSTD_ERR_NOT_FOUND;
}

cstd_status cstd_hashmap_free(cstd_hashmap *map) {
    if (map == NULL) {
        return CSTD_ERR_NULL;
    }

    if (map->buckets != NULL) {
        for (size_t i = 0; i < map->capacity; i++) {
            cstd_hashmap_entry *curr = map->buckets[i];
            while (curr != NULL) {
                cstd_hashmap_entry *next = curr->next;
                free(curr->key);
                free(curr->value);
                free(curr);
                curr = next;
            }
        }
    }

    free(map->buckets);
    map->buckets = NULL;
    map->size = 0U;
    map->key_size = 0U;
    map->value_size = 0U;
    map->capacity = 0U;
    map->key_eq = NULL;

    return CSTD_OK;
}

size_t cstd_hashmap_size(const cstd_hashmap *map) {
    if (map == NULL) {
        return 0U;
    }
    return map->size;
}

bool cstd_hashmap_is_empty(const cstd_hashmap *map) {
    return cstd_hashmap_size(map) == 0U;
}
