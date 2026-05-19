# status

Canonical status codes returned by API operations.

| Code | Meaning | Typical trigger |
|---|---|---|
| `CKIT_OK` | Success | Operation completed |
| `CKIT_ERR_NULL` | Null pointer input | Required input pointer is `NULL` |
| `CKIT_ERR_EMPTY` | Empty container state | Pop or peek on an empty container |
| `CKIT_ERR_NOT_FOUND` | Missing key/item | Lookup or removal target does not exist |
| `CKIT_ERR_RANGE` | Invalid value range | `elem_size == 0` in init |
| `CKIT_ERR_STATE` | Invalid runtime state | Internal state does not permit operation |
