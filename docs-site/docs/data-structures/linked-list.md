# Linked List

## Operations

| Operation | API | Complexity | Status | Notes |
|---|---|---|---|---|
| Push tail | `cstd_linked_list_push` | O(1) | Implemented | Appends node at tail |
| Push front | `cstd_linked_list_pushfront` | O(1) | Implemented | Prepends node at head |
| Pop left | `cstd_linked_list_popleft` | O(1) | Implemented | Removes and returns head value |
| Is empty | `cstd_linked_list_is_empty` | O(1) | Implemented | Checks whether size is zero |
| Traverse/search | n/a | O(n) | Conceptual | Linear walk over nodes |

## API usage

```c
#include <cstd/datastruct/linked_list.h>
#include <cstd/status.h>
#include <stdint.h>

int main(void) {
    cstd_linked_list list;
    if (cstd_linked_list_init(&list, sizeof(uint64_t)) != CSTD_OK) {
        return 1;
    }

    uint64_t tail_value = 7;
    uint64_t front_value = 9;
    uint64_t out = 0;

    if (cstd_linked_list_is_empty(&list)) {
        /* expected before first push */
    }

    if (cstd_linked_list_push(&list, &tail_value) != CSTD_OK) {
        cstd_linked_list_free(&list);
        return 1;
    }

    if (cstd_linked_list_pushfront(&list, &front_value) != CSTD_OK) {
        cstd_linked_list_free(&list);
        return 1;
    }

    if (cstd_linked_list_popleft(&list, &out) != CSTD_OK) {
        cstd_linked_list_free(&list);
        return 1;
    }

    cstd_linked_list_free(&list);
    return 0;
}
```

## Benchmark snapshot

Current run summary:

| Case | Median (ns/op) | Throughput (ops/sec) |
|---|---:|---:|
| `steady_push` | 18.820 | 53,134,343 |
| `push_plus_free` | 24.903 | 40,156,382 |
| `steady_pushfront_popleft` | 13.589 | 73,589,620 |
