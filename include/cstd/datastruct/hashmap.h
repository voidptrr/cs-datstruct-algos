#ifndef CSTD_DATASTRUCT_HASHMAP_H
#define CSTD_DATASTRUCT_HASHMAP_H

#include <stdbool.h>
#include <stddef.h>

#include "cstd/status.h"

/*
 * Hash map with separate chaining.
 *
 * cstd_hashmap
 * +--------------------------------------------------------------------------+
 * | size | key_size | value_size | capacity | buckets | key_eq               |
 * +--------------------------------------------------------------------------+
 *                                            |
 *                                            v
 * buckets (array of entry-head pointers)
 * +---------+---------+---------+---------+---------+
 * | [0]     | [1]     | [2]     | [3]     | [4]     |
 * +----+----+----+----+----+----+----+----+----+----+
 *      |         |                   |
 *      v         v                   v
 *    NULL      +-------+      +-------+ -> +-------+ -> NULL
 *              | kA,vA |      | kB,vB |    | kC,vC |
 *              +---+---+      +---+---+    +---+---+
 *                  |              |
 *                  v              v
 *                NULL           NULL
 *
 * Example collision chain at one bucket:
 * buckets[3] -> [kB,vB] -> [kC,vC] -> NULL
 */

/* Key equality callback used to resolve collisions and lookups. */
typedef bool (*cstd_hashmap_key_eq_fn)(const void *lhs, const void *rhs, size_t key_size);

/* One chained entry stored inside a bucket list. */
typedef struct cstd_hashmap_entry {
    void *key;
    void *value;
    struct cstd_hashmap_entry *next;
} cstd_hashmap_entry;

/* Hash map object and its bucket array metadata. */
typedef struct cstd_hashmap {
    size_t size;
    size_t key_size;
    size_t value_size;
    size_t capacity;
    cstd_hashmap_entry **buckets;
    cstd_hashmap_key_eq_fn key_eq;
} cstd_hashmap;

/*
 * Initialize a hash map with fixed key/value sizes.
 * Hashing uses the internal FNV-1a implementation.
 * Initial capacity is implementation-defined.
 */
cstd_status cstd_hashmap_init(cstd_hashmap *map, size_t key_size, size_t value_size,
                              cstd_hashmap_key_eq_fn key_eq);

/*
 * Insert or update an entry.
 * If key exists, overwrite value in place.
 */
cstd_status cstd_hashmap_put(cstd_hashmap *map, const void *key, const void *value);

/*
 * Lookup key and copy value into out_value.
 */
cstd_status cstd_hashmap_get(const cstd_hashmap *map, const void *key, void *out_value);

/*
 * Remove key from map.
 */
cstd_status cstd_hashmap_remove(cstd_hashmap *map, const void *key);

/*
 * Release all entries and bucket storage, reset map to empty state.
 */
cstd_status cstd_hashmap_free(cstd_hashmap *map);

/* Return the number of stored entries. */
size_t cstd_hashmap_size(const cstd_hashmap *map);

/* Return whether map has zero entries. */
bool cstd_hashmap_is_empty(const cstd_hashmap *map);

#endif
