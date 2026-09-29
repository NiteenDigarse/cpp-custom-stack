# CustomStack

A generic **C++20 Stack implementation** built using composition with a custom dynamic array container, `CustomVector`.

The project focuses on understanding **composition, adapter-style design, LIFO semantics, const-correct API design, exception handling, testing, and benchmarking**.

---

## Features

* Generic template-based Stack
* LIFO (Last In, First Out) behavior
* `push()` with lvalue and rvalue overloads
* `pop()`
* `top()`
* `empty()`
* `size()`
* Const-correct `top()` API
* Exception handling for invalid empty-stack operations
* Uses `CustomVector<T>` as underlying storage
* Comprehensive test suite
* Benchmark against `std::stack`
* C++20 support

---

## Architecture

CustomStack uses **composition** rather than implementing its own dynamic storage.

```text
                    CustomStack<T>
                         |
                         | HAS-A
                         ↓
                  CustomVector<T>
                         |
                         ↓
                Dynamic Memory Storage
```

### Separation of Responsibilities

| Component      | Responsibility                                         |
| -------------- | ------------------------------------------------------ |
| `CustomStack`  | LIFO behavior and Stack API                            |
| `CustomVector` | Storage, allocation, reallocation, and object lifetime |

This allows the Stack to reuse the low-level functionality already implemented by `CustomVector`.

---

## API

### Push

```cpp
CustomStack<int> stack;

stack.push(10);

int value = 20;
stack.push(value);

stack.push(30);
```

Both lvalue and rvalue overloads are supported.

---

### Top

```cpp
stack.top();
```

Returns the element at the top of the Stack.

The implementation provides both mutable and const overloads:

```cpp
T& top();

const T& top() const;
```

---

### Pop

```cpp
stack.pop();
```

Removes the top element.

Attempting to pop an empty Stack throws `std::out_of_range`.

---

### Empty

```cpp
stack.empty();
```

Returns `true` when the Stack contains no elements.

---

### Size

```cpp
stack.size();
```

Returns the number of elements currently stored.

---

## Example

```cpp
#include <iostream>
#include "custom_stack.h"

int main()
{
    CustomStack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << stack.top() << '\n';  // 30

    stack.pop();

    std::cout << stack.top() << '\n';  // 20

    return 0;
}
```

Output:

```text
30
20
```

---

## LIFO Behavior

Stack follows the **Last In, First Out** principle.

```text
push(10)
push(20)
push(30)

      TOP
       ↓
      [30]
      [20]
      [10]

pop() → 30
pop() → 20
pop() → 10
```

---

## Error Handling

Invalid operations on an empty Stack are handled using `std::out_of_range`.

```cpp
CustomStack<int> stack;

stack.top(); // throws std::out_of_range
stack.pop(); // throws std::out_of_range
```

---

## Testing

The project contains a dedicated test executable covering:

* Empty Stack
* Push
* Pop
* Top
* Size
* Empty
* LIFO behavior
* Pop all elements
* `int` Stack
* `std::string` Stack
* Empty `top()`
* Empty `pop()`
* Repeated push/pop operations
* Lvalue push
* Rvalue push
* Mutable `top()`

All implemented tests pass successfully.

---

## Benchmark

The project includes a benchmark comparing:

```text
CustomStack<int>
       VS
std::stack<int>
```

### Workload

* 1,000,000 elements
* 1,000,000 push operations
* 1,000,000 pop operations

### Sample Local Run

| Implementation |      Push |       Pop |     Total |
| -------------- | --------: | --------: | --------: |
| CustomStack    | 15,165 µs |  7,706 µs | 22,871 µs |
| `std::stack`   | 20,299 µs | 16,377 µs | 36,676 µs |

> Benchmark results are environment-dependent and should not be interpreted as universal performance results.

---

## Project Structure

```text
cpp-custom-stack/
│
├── CMakeLists.txt
│
├── include/
│   └── custom_stack.h
│
├── src/
│   └── custom_stack.cpp
│
├── tests/
│   └── test_custom_stack.cpp
│
├── benchmarks/
│   └── benchmark_custom_stack.cpp
│
├── docs/
│   ├── architecture.md
│   ├── memory-model.md
│   ├── learning-notes.md
│   └── testing.md
│
├── external/
│   └── custom-vector/
│
└── README.md
```

---

## Build

### Requirements

* C++20 compiler
* CMake 3.20+
* MinGW / GCC or another C++20-compatible compiler

### Configure

```bash
cmake -S . -B build -G "MinGW Makefiles"
```

### Build

```bash
cmake --build build --config Release
```

---

## Run Tests

```bash
build/test_custom_stack.exe
```

---

## Run Benchmark

```bash
build/benchmark_custom_stack.exe
```

---

## Dependency

This project uses [`CustomVector`](https://github.com/NiteenDigarse/cpp-custom-vector) as a Git submodule.

CustomVector provides the underlying dynamic storage and object lifetime management required by CustomStack.

---

## Learning Focus

This project was built as part of a larger C++ Engineering project series.

Key concepts practiced:

* Templates
* Composition
* Adapter design
* LIFO data structures
* API design
* Const-correctness
* Lvalue/rvalue references
* Move semantics
* Exception handling
* Testing
* Benchmarking
* CMake
* Git submodules
* Reusable C++ components

---

## License

MIT License
