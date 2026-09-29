#pragma once

#include <utility>
#include <stdexcept>
#include<iostream>
#include "custom_vector.hpp"

template <typename T>
class CustomStack
{
public:

    // --------------------------------------------------
    // Push lvalue
    // --------------------------------------------------

    void push(const T& value)
    {
        storage_.push_back(value);
    }


    // --------------------------------------------------
    // Push rvalue
    // --------------------------------------------------

    void push(T&& value)
    {
        storage_.push_back(std::move(value));
    }


    // --------------------------------------------------
    // Top - non-const stack
    // --------------------------------------------------

    T& top()
    {
        return storage_.back();
    }


    // --------------------------------------------------
    // Top - const stack
    // --------------------------------------------------

    const T& top() const
    {
        return storage_.back();
    }


    // --------------------------------------------------
    // Pop
    // --------------------------------------------------

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


    // --------------------------------------------------
    // Check whether stack is empty
    // --------------------------------------------------

    bool empty() const
    {
        return storage_.empty();
    }


    // --------------------------------------------------
    // Return number of elements
    // --------------------------------------------------

    std::size_t size() const
    {
        return storage_.size();
    }


private:

    // Underlying storage
    CustomVector<T> storage_;
};