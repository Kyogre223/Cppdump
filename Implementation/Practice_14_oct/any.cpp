//
// Created by Lin Kai on 14/10/24.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <bits/stdc++.h>

class any;


class any {
    template <typename T>
    any(T&& data):ptr_{std::make_unique<Holder<decltype(data)>>(data)}{}

    struct Base {
        virtual ~Base() = default;
        virtual const std::type_info& type() const noexcept = 0;
        virtual std::unique_ptr<Base> clone() const = 0;
    };

    // Derived class template to hold the actual data
    template <typename T>
    struct Holder : Base {
        Holder(T&& value) : data_(std::forward<T>(value)) {}
        Holder(const T& value) : data_(value) {}

        const std::type_info& type() const noexcept override {
                return typeid(T);
        }

        std::unique_ptr<Base> clone() const override {
            return std::make_unique<Holder<T>>(data_);
        }

        T data_;
    };

    std::type_info const& type() const {
        return ptr_->type();
    }

    void* get() const {
        return ptr_.get();
    }
    template <typename T>
    friend T my_any_cast(any const& other) {
        if (typeid(T) != other.type()) {
            throw std::bad_any_cast();
        }
        return static_cast<T>(othe bhhyr.get());
    }
    std::unique_ptr<Base> ptr_;

};

int main() {





    return 0;
}
