function(dsa_add_benchmark TARGET_NAME SOURCE_FILE)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs LIB_SOURCES)
  cmake_parse_arguments(DSA_BENCH "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  add_executable(${TARGET_NAME} ${SOURCE_FILE} ${DSA_BENCH_LIB_SOURCES})
  target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/benchmarks")
  target_compile_definitions(${TARGET_NAME} PRIVATE _POSIX_C_SOURCE=200809L)
endfunction()

set(DSA_BENCH_QUEUE_TARGET "bench-queue-push-pop")
set(DSA_BENCH_VECTOR_TARGET "bench-vector-push-pop")

dsa_add_benchmark(
  ${DSA_BENCH_QUEUE_TARGET}
  "${CMAKE_SOURCE_DIR}/benchmarks/queue_push_pop_bench.c"
  LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/datastruct/queue.c"
)

dsa_add_benchmark(
  ${DSA_BENCH_VECTOR_TARGET}
  "${CMAKE_SOURCE_DIR}/benchmarks/vector_push_pop_bench.c"
  LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/datastruct/vector.c"
)

add_custom_target(bench-queue
  COMMAND ${DSA_BENCH_QUEUE_TARGET}
  DEPENDS ${DSA_BENCH_QUEUE_TARGET}
  USES_TERMINAL
)

add_custom_target(bench-vector
  COMMAND ${DSA_BENCH_VECTOR_TARGET}
  DEPENDS ${DSA_BENCH_VECTOR_TARGET}
  USES_TERMINAL
)

add_custom_target(bench
  COMMAND ${DSA_BENCH_QUEUE_TARGET}
  COMMAND ${DSA_BENCH_VECTOR_TARGET}
  DEPENDS ${DSA_BENCH_QUEUE_TARGET} ${DSA_BENCH_VECTOR_TARGET}
  USES_TERMINAL
)
