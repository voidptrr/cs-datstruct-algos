#ifndef CSTD_BENCH_PAYLOAD_H
#define CSTD_BENCH_PAYLOAD_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint64_t id;
    uint64_t checksum;
    uint32_t tag;
    uint16_t flags;
    uint8_t bytes[24];
} cstd_bench_payload;

static inline cstd_bench_payload cstd_bench_payload_make(uint64_t seed) {
    cstd_bench_payload payload;
    payload.id = seed;
    payload.checksum = seed * 11400714819323198485ULL;
    payload.tag = (uint32_t)(seed ^ (seed >> 32));
    payload.flags = (uint16_t)(seed & 0xFFFFU);

    for (size_t i = 0; i < sizeof(payload.bytes); i++) {
        payload.bytes[i] = (uint8_t)((seed + i) & 0xFFU);
    }

    return payload;
}

#endif
