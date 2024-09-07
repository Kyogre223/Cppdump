//
// Created by Lin Kai on 7/9/24.
//

#ifndef CPPDUMP_ITERATOR_H
#define CPPDUMP_ITERATOR_H

#include <iostream>
#include <vector>
#include <ranges>
#include <iostream>
#include <numeric> // std::iota


template <typename T>
struct myVector {
    T* data_;
    int size = 0;
    int capacity = 0;

    myVector(int n) : size(n), capacity(n * 2) {
        data_ = new T[n];
    }

    // Define the iterator struct
    struct iterator {
        T* ptr_;
        iterator(T* ptr) : ptr_(ptr) {}

        // Prefix increment
        iterator& operator++() {
            ptr_++;
            return *this;
        }

        // Postfix increment (takes int to distinguish from prefix)
        iterator operator++(int) {
            iterator tmp = *this;  // Save current state
            ptr_++;                // Increment pointer
            return tmp;            // Return saved state (previous position)
        }

        // Dereference operator
        T& operator*() const {
            return *ptr_;
        }

        // Equality comparison
        bool operator==(const iterator& other) const {
            return ptr_ == other.ptr_;
        }

        // Inequality comparison
        bool operator!=(const iterator& other) const {
            return ptr_ != other.ptr_;
        }
    };

    // Begin iterator (points to the first element)
    iterator begin() const {
        return iterator(data_);
    }

    // End iterator (points one past the last element)
    iterator end() const {
        return iterator(data_ + size);
    }

    ~myVector() {
        delete[] data_;
    }
};

#endif //CPPDUMP_ITERATOR_H
