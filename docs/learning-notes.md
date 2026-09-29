# CustomStack — Learning Notes

## 1. Project Goal

The goal of this project was to implement a generic LIFO stack using composition instead of implementing a new dynamic storage system.

The stack uses `CustomVector<T>` as its underlying storage.

```text
User
  ↓
CustomStack<T>
  ↓ HAS-A
CustomVector<T>
  ↓
Dynamic Storage
```

The main learning focus was:

* Composition
* Adapter-style design
* LIFO semantics
* API design
* Const-correctness
* Reusing an existing low-level component
* Template-based generic programming
* Exception handling
* Testing
* Benchmarking

---

# 2. What is a Stack?

A Stack is a LIFO (Last In, First Out) data structure.

If we insert:

```text
10
20
30
```

The stack looks like:

```text
TOP → 30
      20
      10
```

The last inserted element is removed first.

Therefore:

```text
push(10)
push(20)
push(30)

pop() → 30
pop() → 20
pop() → 10
```

---

# 3. Why CustomVector is Used

CustomVector already handles:

* Dynamic memory allocation
* Capacity management
* Reallocation
* Object lifetime
* Copy semantics
* Move semantics
* Element insertion/removal
* Bounds checking

Therefore CustomStack should not duplicate these responsibilities.

CustomStack only needs to provide Stack semantics.

```text
CustomStack
    |
    +-- LIFO behavior
    +-- push()
    +-- pop()
    +-- top()
    +-- empty()
    +-- size()

CustomVector
    |
    +-- Storage
    +-- Memory
    +-- Object lifetime
    +-- Reallocation
```

This is separation of responsibilities.

---

# 4. Composition

CustomStack contains a `CustomVector<T>`:

```cpp
CustomVector<T> storage_;
```

This represents a HAS-A relationship.

```text
CustomStack<int>
       |
       └── HAS-A → CustomVector<int>
```

The stack delegates storage-related operations to the vector.

Example:

```cpp
void push(const T& value)
{
    storage_.push_back(value);
}
```

The Stack does not know how the vector allocates memory internally.

---

# 5. Adapter-Style Design

CustomStack acts as an abstraction layer over CustomVector.

The user sees:

```cpp
stack.push(10);
stack.pop();
stack.top();
```

The user does not directly interact with:

```cpp
storage_.push_back();
storage_.pop_back();
storage_.back();
```

Therefore CustomStack adapts the general-purpose CustomVector storage into a Stack-specific interface.

---

# 6. push()

Two overloads are provided.

## Lvalue

```cpp
void push(const T& value)
{
    storage_.push_back(value);
}
```

Used when the argument is an existing object:

```cpp
int x = 10;

stack.push(x);
```

The value is copied into the underlying storage.

## Rvalue

```cpp
void push(T&& value)
{
    storage_.push_back(std::move(value));
}
```

Used for temporary/rvalue objects:

```cpp
stack.push(10);
stack.push(std::string("Hello"));
```

`std::move()` allows the underlying vector to select its move-based insertion path when appropriate.

---

# 7. top()

The stack's top element is the last element of the underlying vector.

```cpp
T& top()
{
    return storage_.back();
}
```

For a stack:

```text
[10][20][30]
          ↑
         TOP
```

Therefore:

```cpp
storage_.back()
```

returns:

```text
30
```

The const overload is:

```cpp
const T& top() const
{
    return storage_.back();
}
```

This provides const-correctness.

---

# 8. Why Two top() Overloads?

Non-const stack:

```cpp
CustomStack<int> stack;

stack.push(10);

stack.top() = 50;
```

This is allowed because:

```cpp
T& top();
```

returns a modifiable reference.

For a const stack:

```cpp
const CustomStack<int> stack;
```

the const overload is selected:

```cpp
const T& top() const;
```

The returned element cannot be modified.

---

# 9. pop()

The Stack does not remove elements directly from memory.

It delegates to CustomVector:

```cpp
void pop()
{
    if (storage_.empty())
    {
        throw std::out_of_range(
            "CustomStack::pop() called on empty stack"
        );
    }

    storage_.pop_back();
}
```

Flow:

```text
stack.pop()
    ↓
storage_.pop_back()
    ↓
last element removed
```

This maintains LIFO behavior.

---

# 10. Empty Stack Behavior

Calling `top()` on an empty stack is invalid.

```cpp
CustomStack<int> stack;

stack.top();
```

The underlying `CustomVector::back()` performs the empty check and throws:

```cpp
std::out_of_range
```

Similarly, `CustomStack::pop()` explicitly checks for an empty stack and throws:

```cpp
std::out_of_range
```

This gives CustomStack a clear API contract:

```text
Empty top() → exception
Empty pop() → exception
```

---

# 11. empty()

CustomStack delegates the check to CustomVector:

```cpp
bool empty() const
{
    return storage_.empty();
}
```

The Stack does not maintain a second independent state.

This avoids duplicated state and possible inconsistencies.

---

# 12. size()

CustomStack also delegates size information:

```cpp
std::size_t size() const
{
    return storage_.size();
}
```

Therefore:

```text
CustomStack::size()
        ↓
CustomVector::size()
```

---

# 13. LIFO Verification

The tests verified:

```text
push(10)
push(20)
push(30)
```

Then:

```text
top() → 30

pop()

top() → 20

pop()

top() → 10
```

This confirms that CustomStack follows LIFO semantics.

---

# 14. Generic Template Design

CustomStack is a class template:

```cpp
template <typename T>
class CustomStack
```

Therefore it can work with different types.

Examples:

```cpp
CustomStack<int>
CustomStack<std::string>
```

The tests verified both `int` and `std::string`.

---

# 15. Testing

The test suite covers:

* Empty stack
* Push
* Pop
* Top
* Size
* Empty
* LIFO behavior
* Pop all elements
* `int` stack
* `std::string` stack
* Empty `top()`
* Empty `pop()`
* 1000-element push/pop test
* Lvalue push
* Rvalue push
* Non-const top modification

All tests passed.

---

# 16. Benchmark

A benchmark was created to compare:

```text
CustomStack<int>
        VS
std::stack<int>
```

Workload:

```text
1,000,000 elements
```

Operations:

```text
Push 1,000,000 elements
Pop  1,000,000 elements
```

Measured results from one local run:

```text
CustomStack<int>

Push:  15165 us
Pop:    7706 us
Total: 22871 us


std::stack<int>

Push:  20299 us
Pop:   16377 us
Total: 36676 us
```

These numbers represent one benchmark run on the development machine.

They should not be treated as universal performance results because benchmark results depend on:

* CPU
* Compiler
* Compiler version
* Optimization settings
* Standard library implementation
* Operating system
* System load
* Benchmark methodology

---

# 17. C++20 Requirement

CustomStack uses CustomVector as a dependency.

The CustomVector implementation uses:

```cpp
std::construct_at
```

which requires C++20.

Therefore the CustomStack project is configured for:

```cmake
set(CMAKE_CXX_STANDARD 20)
```

---

# 18. Dependency Structure

CustomVector is included as a Git submodule:

```text
external/
└── custom-vector/
```

This allows CustomStack to reuse the previously developed CustomVector project instead of copying its source code.

The relationship is:

```text
CustomStack Repository
        |
        └── Git Submodule
                |
                └── CustomVector Repository
```

---

# 19. Key Engineering Lessons

### Separation of responsibilities

Do not make every data structure responsible for memory management.

```text
CustomStack → Stack behavior
CustomVector → Storage and memory
```

### Composition

A higher-level component can reuse a lower-level component instead of reimplementing it.

### Delegation

CustomStack delegates storage operations:

```cpp
storage_.push_back()
storage_.pop_back()
storage_.back()
storage_.empty()
storage_.size()
```

### Const-correctness

Providing both:

```cpp
T& top();
const T& top() const;
```

allows correct behavior for both mutable and const objects.

### API contracts

Invalid operations should have clearly defined behavior.

For this Stack:

```text
top() on empty → std::out_of_range
pop() on empty → std::out_of_range
```

### Reuse

A well-designed component becomes a building block for future components.

CustomVector was created first and is now being reused by CustomStack.

---

# 20. Final Architecture

```text
                    CustomStack<T>
                         |
                         | HAS-A
                         ↓
                  CustomVector<T>
                         |
                         ↓
                Dynamic Memory Storage
                         |
                         ↓
               Object Lifetime Management
```

The main design principle is:

> Build low-level components once and compose them into higher-level abstractions.

---

# 21. Project Status

```text
Core implementation       ✅
Composition                ✅
LIFO behavior              ✅
Exception handling        ✅
Const-correctness          ✅
Test suite                 ✅
Edge-case testing          ✅
Benchmark                  ✅
Learning notes             ✅

Next:
Git cleanup → Commit → Push → GitHub
```

