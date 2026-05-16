# Getting Started

This project is used like an extended C standard container module: include `datastruct/*` headers, initialize a container with `elem_size`, perform operations, and handle `cstd_status`.

## Requirements

- Nix with flakes enabled

## Run unit tests

```bash
nix run .#test-all
```

## Run benchmarks

```bash
nix run .#bench-all
```

## Include style

```c
#include <cstd/datastruct/vector.h>
#include <cstd/datastruct/queue.h>
#include <cstd/datastruct/linked_list.h>
#include <cstd/status.h>
```

## Typical container lifecycle

```c
/* 1) init 2) ops 3) free */
```

## Build checks with hardening

```bash
nix run .#code-check
```
