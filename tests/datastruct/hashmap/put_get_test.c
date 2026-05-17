#include <stdint.h>
#include <stdio.h>

#include "cstd/compare.h"
#include "cstd/datastruct/hashmap.h"

int main(void) {
    cstd_hashmap map;
    uint64_t key = 7U;
    uint64_t value = 11U;
    uint64_t value2 = 99U;
    uint64_t out = 0U;

    if (cstd_hashmap_put(NULL, &key, &value) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_hashmap_put(NULL, ...) should return CSTD_ERR_NULL\n");
        return 1;
    }

    if (cstd_hashmap_get(NULL, &key, &out) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_hashmap_get(NULL, ...) should return CSTD_ERR_NULL\n");
        return 1;
    }

    if (cstd_hashmap_init(&map, sizeof(uint64_t), sizeof(uint64_t), cstd_eq_u64) != CSTD_OK) {
        fprintf(stderr, "cstd_hashmap_init should return CSTD_OK\n");
        return 1;
    }

    if (cstd_hashmap_put(&map, NULL, &value) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_hashmap_put NULL key should return CSTD_ERR_NULL\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_put(&map, &key, NULL) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_hashmap_put NULL value should return CSTD_ERR_NULL\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_get(&map, &key, &out) != CSTD_ERR_NOT_FOUND) {
        fprintf(stderr, "cstd_hashmap_get missing key should return CSTD_ERR_NOT_FOUND\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_put(&map, &key, &value) != CSTD_OK) {
        fprintf(stderr, "cstd_hashmap_put should return CSTD_OK\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_get(&map, &key, &out) != CSTD_OK || out != value) {
        fprintf(stderr, "cstd_hashmap_get should return inserted value\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_put(&map, &key, &value2) != CSTD_OK) {
        fprintf(stderr, "cstd_hashmap_put update should return CSTD_OK\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_get(&map, &key, &out) != CSTD_OK || out != value2) {
        fprintf(stderr, "cstd_hashmap_get should return updated value\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_size(&map) != 1U) {
        fprintf(stderr, "cstd_hashmap_size should stay 1 after overwrite\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    cstd_hashmap_free(&map);
    return 0;
}
