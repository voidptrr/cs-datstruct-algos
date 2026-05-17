#include <stdint.h>
#include <stdio.h>

#include "cstd/compare.h"
#include "cstd/datastruct/hashmap.h"

int main(void) {
    cstd_hashmap map;

    if (cstd_hashmap_init(NULL, sizeof(uint64_t), sizeof(uint64_t), cstd_eq_u64) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_hashmap_init(NULL, ...) should return CSTD_ERR_NULL\n");
        return 1;
    }

    if (cstd_hashmap_init(&map, 0U, sizeof(uint64_t), cstd_eq_u64) != CSTD_ERR_RANGE) {
        fprintf(stderr, "cstd_hashmap_init key_size=0 should return CSTD_ERR_RANGE\n");
        return 1;
    }

    if (cstd_hashmap_init(&map, sizeof(uint64_t), 0U, cstd_eq_u64) != CSTD_ERR_RANGE) {
        fprintf(stderr, "cstd_hashmap_init value_size=0 should return CSTD_ERR_RANGE\n");
        return 1;
    }

    if (cstd_hashmap_init(&map, sizeof(uint64_t), sizeof(uint64_t), NULL) != CSTD_ERR_NULL) {
        fprintf(stderr, "cstd_hashmap_init NULL key_eq should return CSTD_ERR_NULL\n");
        return 1;
    }

    if (cstd_hashmap_init(&map, sizeof(uint64_t), sizeof(uint64_t), cstd_eq_u64) != CSTD_OK) {
        fprintf(stderr, "cstd_hashmap_init valid args should return CSTD_OK\n");
        return 1;
    }

    if (cstd_hashmap_size(&map) != 0U || !cstd_hashmap_is_empty(&map)) {
        fprintf(stderr, "new hashmap should be empty\n");
        cstd_hashmap_free(&map);
        return 1;
    }

    if (cstd_hashmap_free(&map) != CSTD_OK) {
        fprintf(stderr, "cstd_hashmap_free should return CSTD_OK\n");
        return 1;
    }

    return 0;
}
