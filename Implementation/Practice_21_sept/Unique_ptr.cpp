//
// Created by Lin Kai on 21/9/24.
//


#include <iostream>
#include <memory>



template <typename T, typename U = std::default_delete<T>>
class Unique_Ptr {
    T* data_;
    U deleter_;
public:
    Unique_Ptr(T* data, U deleter = std::default_delete<T>{}):data_{data}, deleter_{deleter} {
    }
    Unique_Ptr(Unique_Ptr const& other) = delete; // copy constructor delete
    Unique_Ptr& operator = (Unique_Ptr const& other) = delete;

    int use_count() const {
        if (data_) return 1;
        return 0;
    }
    ~Unique_Ptr() {
        if (data_) deleter_(data_);
    }

};

template <typename T, typename... Args>
Unique_Ptr<T> Make_Unique(Args&&... args) {
    return Unique_Ptr<T>(new T(std::forward<Args>(args)...));
}


int main() {



    return 0;
}