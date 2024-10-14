//
// Created by Lin Kai on 14/10/24.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <bits/stdc++.h>

// shared pointer.
// even with custom deleter types, there is type erasure here

// custom deleter type is type erased.
namespace Impl {

    struct MyDelete {
        template <typename T>
        void operator () (T* ptr) {
            delete ptr;
        }
    };

    template <typename T, typename deleter = std::default_delete<T>>
    class SharedPointer {
    public:
        SharedPointer() {
            del_ = std::make_unique<Child<std::default_delete<T>>>();
            ref_count_ = new int(0);
        }
        template <typename U>
        SharedPointer(U* data, deleter del = std::default_delete<U>{}):
                data_{data},
                ref_count_{new int(0)}
        {
            increment();

        }

        void increment() {
            ++(*ref_count_);
        }

        void decrement() {
            --(*ref_count_);
            if (*ref_count_ == 0) {
                delete ref_count_;
                (*del_)(data_);
            }
        }

        ~SharedPointer() noexcept {
            decrement();
            ref_count_ = nullptr;
            data_ = nullptr;
        }
        SharedPointer(SharedPointer const& other) {
            ref_count_ = other.ref_count_;
            increment();
            data_ = other.data_;
        }

        SharedPointer& operator = (SharedPointer const& other) {
            if (this == &other) return *this;
            ref_count_ = other.ref_count_;
            increment();
            data_ = other.data_;
            return *this;
        }

        size_t use_count() const {
            return *ref_count_;
        }

        T* get() const {
            return data_;
        }

        template <typename U, typename... Args>
        friend SharedPointer<U> make_shared(Args... args);

    private:
        struct Base {
            virtual void operator () (void* ptr) = 0;
        };

        template <typename U>
        struct Child : public Base {
            Child(U&& arg): deleter_{arg}{}
            void operator () (void* ptr) override {
                deleter_(static_cast<U*>(ptr));
            }
            U deleter_;
        };
        int* ref_count_;
        T* data_;
        std::unique_ptr<Base> del_;

        // some other mutex and the control block etc.....
    };

    template <typename T, typename... Args>
    SharedPointer<T> make_shared(Args... args) {
        return SharedPointer<T>(new T(std::forward<Args>(args)...));
    }
}


int main() {
    using namespace Impl;
    SharedPointer<int>ptr(new int(10));
    std::cout << ptr.use_count() << '\n';
    SharedPointer<int>ptr2 = ptr;
    std::cout << ptr2.use_count() << '\n';
    std::cout << ptr.use_count() << '\n';



    return 0;
}