//
// Created by Lin Kai on 17/9/24.
//

#ifndef CPPDUMP_UNIQUE_PTR_H
#define CPPDUMP_UNIQUE_PTR_H


#include <iostream>
#include <memory>

// unique ptr
// shared_ptr
// string ?
// malloc

template <typename T, typename T2 = std::default_delete<T>>
struct Unique_Ptr {
    T* data_;
    T2 deleter_;
    Unique_Ptr(T* ptr, T2 deleter) {
        data_ = ptr;
        deleter_ = deleter;
    }

    // delete copy constructor
    Unique_Ptr(Unique_Ptr const& other) = delete;
    Unique_Ptr(Unique_Ptr&& other) noexcept {
        data_ = other.data_;
        deleter_ = std::move(other.deleter_);
        other.data_ = nullptr;
    }

    Unique_Ptr& operator=(Unique_Ptr&& other) noexcept {
        if (this != &other) {
            deleter_(data_);
            data_ = other.data_;
            deleter_ = std::move(other.deleter_);
            other.data_ = nullptr;
        }
        return *this;
    }
    size_t use_count() const {
        if (data_ == nullptr) return 0;
        return 1;
    }
    void release() {
        deleter_(data_);
    }

    void swap(Unique_Ptr& other) {
        std::swap(data_, other.data_);
        std::swap(deleter_, other.deleter_);
    }

    void reset(T* data) {
        deleter_(data_);
        data_ = data;
    }

    ~Unique_Ptr() {
        deleter_(data_);
    }

    T* get() const {
        return data_;
    }

    T2 get_deleter() const {
        return deleter_;
    }

    operator bool () {
        return data_ != nullptr;
    }

    T* operator -> () const {
        return data_;
    }

};




int main() {

    return 0;
}



#endif //CPPDUMP_UNIQUE_PTR_H
