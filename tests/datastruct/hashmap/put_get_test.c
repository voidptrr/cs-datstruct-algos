#include <stdint.h>
#include <stdio.h>

#include "ckit/compare.h"
#include "ckit/datastruct/hashmap.h"

int main(void) {
    ckit_hashmap map;
    uint64_t key = 7U;
    uint64_t value = 11U;
    uint64_t value2 = 99U;
    uint64_t out = 0U;

    if (ckit_hashmap_put(NULL, &key, &value) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_hashmap_put(NULL, ...) should return CKIT_ERR_NULL\n");
        return 1;
    }

    if (ckit_hashmap_get(NULL, &key, &out) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_hashmap_get(NULL, ...) should return CKIT_ERR_NULL\n");
        return 1;
    }

    if (ckit_hashmap_init(&map, sizeof(uint64_t), sizeof(uint64_t), ckit_eq_u64) != CKIT_OK) {
        fprintf(stderr, "ckit_hashmap_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_hashmap_put(&map, NULL, &value) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_hashmap_put NULL key should return CKIT_ERR_NULL\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_put(&map, &key, NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_hashmap_put NULL value should return CKIT_ERR_NULL\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_get(&map, &key, &out) != CKIT_ERR_NOT_FOUND) {
        fprintf(stderr, "ckit_hashmap_get missing key should return CKIT_ERR_NOT_FOUND\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_put(&map, &key, &value) != CKIT_OK) {
        fprintf(stderr, "ckit_hashmap_put should return CKIT_OK\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_get(&map, &key, &out) != CKIT_OK || out != value) {
        fprintf(stderr, "ckit_hashmap_get should return inserted value\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_put(&map, &key, &value2) != CKIT_OK) {
        fprintf(stderr, "ckit_hashmap_put update should return CKIT_OK\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_get(&map, &key, &out) != CKIT_OK || out != value2) {
        fprintf(stderr, "ckit_hashmap_get should return updated value\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_size(&map) != 1U) {
        fprintf(stderr, "ckit_hashmap_size should stay 1 after overwrite\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    ckit_hashmap_free(&map);
    return 0;
}
