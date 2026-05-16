# Overview

`cstd` is an enhanced standard-library style layer for C: familiar container primitives with consistent APIs, explicit status codes, and benchmark-backed performance.

## Why cstd

- Keep the ergonomics of a "standard" container module in plain C.
- Use one naming scheme and one error model across containers.
- Make behavior predictable in low-level code and embedded-style workflows.
- Keep performance visible with repeatable benchmark runs.

## Current containers

- `vector`
- `queue`
- `linked_list`

## API style

- Typedef-first public types (for less noisy call sites).
- `cstd_status` return values instead of hidden failure states.
- Generic element storage via `elem_size` + copy-based operations.
