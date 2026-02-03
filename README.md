# BinaryCodeWord

A small C++20 library that models a binary codeword stored as a contiguous `int[]` and supports
component-wise XOR via `operator+` and `operator+=`.

## Build (library only)

```bash
cmake -S . -B build
cmake --build build
```

## Build examples

```bash
cmake -S . -B build -DBCW_BUILD_EXAMPLES=ON
cmake --build build
./build/examples/bcw_example_basic
```

## Build tests

```bash
cmake -S . -B build -DBCW_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build
```

## Consume via FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
  BinaryCodeWord
  GIT_REPOSITORY https://github.com/<you>/BinaryCodeWord.git
  GIT_TAG v0.1.0
)

set(BCW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BCW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(BinaryCodeWord)

target_link_libraries(your_target PRIVATE BinaryCodeWord::BinaryCodeWord)
```
