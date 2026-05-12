cmake_minimum_required(VERSION 3.20)

project(algorithms_and_data_structures_c C)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

function(add_dsa_test TARGET_KEY TEST_FILE)
  string(REPLACE "/" ";" TARGET_PARTS "${TARGET_KEY}")
  list(LENGTH TARGET_PARTS TARGET_PARTS_LEN)

  if(NOT TARGET_PARTS_LEN EQUAL 2)
    message(FATAL_ERROR "TARGET must be in format <group>/<name>, got: ${TARGET_KEY}")
  endif()

  list(GET TARGET_PARTS 0 TARGET_GROUP)
  list(GET TARGET_PARTS 1 TARGET_NAME_RAW)

  set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/src/${TARGET_NAME_RAW}.c")
  if(NOT EXISTS "${SOURCE_FILE}")
    message(FATAL_ERROR "Missing source file for ${TARGET_KEY}: ${SOURCE_FILE}")
  endif()

  string(REPLACE "/" "-" EXECUTABLE_NAME "${TARGET_KEY}")

  add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE} ${TEST_FILE})
  target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")
  add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endfunction()

if(DEFINED TARGET)
  set(TEST_FILE "${CMAKE_SOURCE_DIR}/tests/${TARGET}_test.c")
  if(NOT EXISTS "${TEST_FILE}")
    message(FATAL_ERROR "Missing test file: ${TEST_FILE}")
  endif()
  add_dsa_test("${TARGET}" "${TEST_FILE}")
else()
  file(GLOB TEST_FILES RELATIVE "${CMAKE_SOURCE_DIR}" "tests/*/*_test.c")
  if(NOT TEST_FILES)
    message(WARNING "No tests found under tests/*/*_test.c")
  endif()

  foreach(TEST_FILE_REL ${TEST_FILES})
    get_filename_component(TEST_DIR "${TEST_FILE_REL}" DIRECTORY)
    get_filename_component(TARGET_GROUP "${TEST_DIR}" NAME)
    get_filename_component(TEST_BASENAME "${TEST_FILE_REL}" NAME_WE)
    string(REGEX REPLACE "_test$" "" TARGET_NAME_RAW "${TEST_BASENAME}")
    set(TARGET_KEY "${TARGET_GROUP}/${TARGET_NAME_RAW}")
    add_dsa_test("${TARGET_KEY}" "${CMAKE_SOURCE_DIR}/${TEST_FILE_REL}")
  endforeach()
endif()
