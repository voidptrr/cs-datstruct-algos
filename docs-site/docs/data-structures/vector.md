# Vector

## Operations

| Operation | API | Complexity | Notes |
|---|---|---|---|
| Push back | `cstd_vector_push` | Amortized O(1) | Can trigger growth/realloc |
| Pop back | `cstd_vector_pop` | O(1) | Fails on empty vector |
| Is empty | `cstd_vector_is_empty` | O(1) | Checks whether size is zero |

## API usage

```c
#include <cstd/datastruct/vector.h>
#include <cstd/status.h>
#include <stdint.h>

int main(void) {
    cstd_vector vec;
    if (cstd_vector_init(&vec, sizeof(uint64_t)) != CSTD_OK) {
        return 1;
    }

    uint64_t value = 42;
    if (cstd_vector_is_empty(&vec)) {
        /* expected before first push */
    }

    if (cstd_vector_push(&vec, &value) != CSTD_OK) {
        cstd_vector_free(&vec);
        return 1;
    }

    uint64_t out = 0;
    if (cstd_vector_pop(&vec, &out) != CSTD_OK) {
        cstd_vector_free(&vec);
        return 1;
    }

    cstd_vector_free(&vec);
    return 0;
}
```

## Benchmark snapshot

Current run summary:

| Case | Median (ns/op) | Throughput (ops/sec) |
|---|---:|---:|
| `steady_push_pop` | 5.054 | 197,860,420 |
| `growth_push_pop` | 8.319 | 120,208,002 |
