# Queue

## Operations

| Operation | API | Complexity | Notes |
|---|---|---|---|
| Push back | `cstd_queue_push` | Amortized O(1) | Can trigger growth/realloc |
| Push front | `cstd_queue_pushfront` | Amortized O(1) | Can trigger growth/realloc |
| Pop left | `cstd_queue_popleft` | O(1) | Fails on empty queue |
| Pop back | `cstd_queue_popback` | O(1) | Fails on empty queue |
| Peek left | `cstd_queue_peekleft` | O(1) | Reads front element without removing |
| Peek back | `cstd_queue_peekback` | O(1) | Reads back element without removing |
| Is empty | `cstd_queue_is_empty` | O(1) | Checks whether size is zero |

## API usage

```c
#include <cstd/datastruct/queue.h>
#include <cstd/status.h>
#include <stdint.h>

int main(void) {
    cstd_queue q;
    if (cstd_queue_init(&q, sizeof(uint64_t)) != CSTD_OK) {
        return 1;
    }

    uint64_t first = 10;
    uint64_t second = 20;
    if (cstd_queue_is_empty(&q)) {
        /* expected before first push */
    }

    cstd_queue_push(&q, &first);
    cstd_queue_pushfront(&q, &second);

    uint64_t out = 0;
    cstd_queue_peekleft(&q, &out);
    cstd_queue_peekback(&q, &out);
    cstd_queue_popleft(&q, &out);
    cstd_queue_popback(&q, &out);

    cstd_queue_free(&q);
    return 0;
}
```

## Benchmark snapshot

Current run summary:

| Case | Median (ns/op) | Throughput (ops/sec) |
|---|---:|---:|
| `steady_push_pop` | 4.990 | 200,400,702 |
| `growth_push_pop` | 12.240 | 81,698,228 |
| `steady_pushfront_popback` | 4.947 | 202,128,643 |
| `growth_pushfront_popback` | 12.141 | 82,364,056 |
