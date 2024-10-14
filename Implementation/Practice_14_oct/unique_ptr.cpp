#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <bits/stdc++.h>


class MyDelete {
public:
    template <typename T>
    void operator () (T* ptr) {
        delete ptr;
    }
};

template <typename T, typename deleter = std::default_delete<T>>
class UniquePointer;

template <typename T, typename U>
UniquePointer<T> make_unique(U&& data) {
    return UniquePointer<T>(std::forward<decltype(data)>(data));
}


template <typename T, typename deleter>
class UniquePointer {
public:
    // constructor
    template <typename U>
    UniquePointer(U&& data, deleter delet = std::default_delete<T>{}):ptr_{new U(std::forward<U>(data))}, deleter_{delet}{
    }
    UniquePointer(UniquePointer const& other) = delete; // copy ctor

    UniquePointer& operator = (UniquePointer const& other) = delete;

    // move ctor
    UniquePointer(UniquePointer&& other) noexcept {
        if (this == &other) return;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    // move assignment
    UniquePointer& operator = (UniquePointer&& other) {
        if (this == &other) return *this;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    // destructor
    ~UniquePointer() {
        if (ptr_) deleter(ptr_);
    }

    template <typename U>
    friend UniquePointer<T> make_unique(U&& data);


private:
    T* ptr_;
    deleter deleter_;
};


int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(10);
    MyDelete del;
    std::unique_ptr<int, MyDelete> ptr2s(new int(10), del);
    std::unique_ptr<int, MyDelete> ptr3s(new int(20), del);

    static_assert(std::is_same_v<decltype(ptr2s), decltype(ptr3s)>, "Types  Match!");
    static_assert(!std::is_same_v<decltype(ptr), decltype(ptr2s)>, "They are not the same!");


    return 0;
}
