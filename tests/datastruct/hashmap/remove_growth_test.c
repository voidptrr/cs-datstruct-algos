#include <stdint.h>
#include <stdio.h>

#include "cstd/compare.h"
#include "cstd/datastruct/hashmap.h"

int main(void) {
    cstd_hashmap map;

    if (cstd_hashmap_init(&map, sizeof(uint64_t), sizeof(uint64_t), cstd_eq_u64) != CSTD_OK) {
        fprintf(stderr, "cstd_hashmap_init should return CSTD_OK\n");
        return 1;
    }

    if (cstd_hashmap_remove(NULL, NULL) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_hashmap_remove(NULL, ...) should return CSTD_ERR_NULL\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    uint64_t missing = 1U;
    if (cstd_hashmap_remove(&map, &missing) != CSTD_ERR_NOT_FOUND) {
        fprintf(stderr, "cstd_hashmap_remove missing key should return CSTD_ERR_NOT_FOUND\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    for (uint64_t i = 0U; i < 512U; i++) {
        uint64_t value = i * 3U;
        if (cstd_hashmap_put(&map, &i, &value) != CSTD_OK) {
            fprintf(stderr, "cstd_hashmap_put should succeed during growth\n");
            cstd_hashmap_free(&map);
            return 1;
        }
    }

    if (cstd_hashmap_size(&map) != 512U) {
        fprintf(stderr, "cstd_hashmap_size should be 512 after inserts\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    for (uint64_t i = 0U; i < 512U; i++) {
        uint64_t out = 0U;
        uint64_t expected = i * 3U;
        if (cstd_hashmap_get(&map, &i, &out) != CSTD_OK || out != expected) {
            fprintf(stderr, "cstd_hashmap_get should find all grown entries\n");
            cstd_hashmap_free(&map);
            return 1;
        }
    }

    uint64_t remove_key = 300U;
    if (cstd_hashmap_remove(&map, &remove_key) != CSTD_OK) {
        fprintf(stderr, "cstd_hashmap_remove existing key should return CSTD_OK\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_get(&map, &remove_key, &missing) != CSTD_ERR_NOT_FOUND) {
        fprintf(stderr, "removed key should not be found\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_size(&map) != 511U) {
        fprintf(stderr, "size should decrease after remove\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    cstd_hashmap_free(&map);
    return 0;
}
