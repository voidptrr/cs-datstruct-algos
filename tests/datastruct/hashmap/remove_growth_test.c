#include <stdint.h>
#include <stdio.h>

#include "ckit/compare.h"
#include "ckit/datastruct/hashmap.h"

int main(void) {
    ckit_hashmap map;

    if (ckit_hashmap_init(&map, sizeof(uint64_t), sizeof(uint64_t), ckit_eq_u64) != CKIT_OK) {
        fprintf(stderr, "ckit_hashmap_init should return CKIT_OK\n");
        return 1;
    }

    if (ckit_hashmap_remove(NULL, NULL) != CKIT_ERR_NULL) {
        fprintf(stderr, "ckit_hashmap_remove(NULL, ...) should return CKIT_ERR_NULL\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    uint64_t missing = 1U;
    if (ckit_hashmap_remove(&map, &missing) != CKIT_ERR_NOT_FOUND) {
        fprintf(stderr, "ckit_hashmap_remove missing key should return CKIT_ERR_NOT_FOUND\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    for (uint64_t i = 0U; i < 512U; i++) {
        uint64_t value = i * 3U;
        if (ckit_hashmap_put(&map, &i, &value) != CKIT_OK) {
            fprintf(stderr, "ckit_hashmap_put should succeed during growth\n");
            ckit_hashmap_free(&map);
            return 1;
        }
    }

    if (ckit_hashmap_size(&map) != 512U) {
        fprintf(stderr, "ckit_hashmap_size should be 512 after inserts\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    for (uint64_t i = 0U; i < 512U; i++) {
        uint64_t out = 0U;
        uint64_t expected = i * 3U;
        if (ckit_hashmap_get(&map, &i, &out) != CKIT_OK || out != expected) {
            fprintf(stderr, "ckit_hashmap_get should find all grown entries\n");
            ckit_hashmap_free(&map);
            return 1;
        }
    }

    uint64_t remove_key = 300U;
    if (ckit_hashmap_remove(&map, &remove_key) != CKIT_OK) {
        fprintf(stderr, "ckit_hashmap_remove existing key should return CKIT_OK\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_get(&map, &remove_key, &missing) != CKIT_ERR_NOT_FOUND) {
        fprintf(stderr, "removed key should not be found\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    if (ckit_hashmap_size(&map) != 511U) {
        fprintf(stderr, "size should decrease after remove\n");
        ckit_hashmap_free(&map);
        return 1;
    }

    ckit_hashmap_free(&map);
    return 0;
}
