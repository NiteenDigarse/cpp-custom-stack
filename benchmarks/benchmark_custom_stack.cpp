#include <chrono>
#include <iostream>
#include <stack>

#include "custom_stack.h"

constexpr std::size_t N = 1'000'000;


// ==================================================
// Benchmark CustomStack
// ==================================================

void benchmark_custom_stack()
{
    CustomStack<int> stack;

    auto start_push = std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < N; ++i)
    {
        stack.push(static_cast<int>(i));
    }

    auto end_push = std::chrono::steady_clock::now();


    auto start_pop = std::chrono::steady_clock::now();

    while (!stack.empty())
    {
        stack.pop();
    }

    auto end_pop = std::chrono::steady_clock::now();


    auto push_time =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end_push - start_push
        ).count();

    auto pop_time =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end_pop - start_pop
        ).count();


    std::cout << "\nCustomStack<int>\n";
    std::cout << "Push: "
              << push_time
              << " us\n";

    std::cout << "Pop:  "
              << pop_time
              << " us\n";

    std::cout << "Total: "
              << push_time + pop_time
              << " us\n";
}


// ==================================================
// Benchmark std::stack
// ==================================================

void benchmark_std_stack()
{
    std::stack<int> stack;

    auto start_push = std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < N; ++i)
    {
        stack.push(static_cast<int>(i));
    }

    auto end_push = std::chrono::steady_clock::now();


    auto start_pop = std::chrono::steady_clock::now();

    while (!stack.empty())
    {
        stack.pop();
    }

    auto end_pop = std::chrono::steady_clock::now();


    auto push_time =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end_push - start_push
        ).count();

    auto pop_time =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end_pop - start_pop
        ).count();


    std::cout << "\nstd::stack<int>\n";
    std::cout << "Push: "
              << push_time
              << " us\n";

    std::cout << "Pop:  "
              << pop_time
              << " us\n";

    std::cout << "Total: "
              << push_time + pop_time
              << " us\n";
}


// ==================================================
// Main
// ==================================================

int main()
{
    std::cout << "====================================\n";
    std::cout << "       CustomStack Benchmark\n";
    std::cout << "====================================\n";

    std::cout << "\nElements: "
              << N << '\n';

    benchmark_custom_stack();

    benchmark_std_stack();

    std::cout << "\n====================================\n";

    return 0;
}