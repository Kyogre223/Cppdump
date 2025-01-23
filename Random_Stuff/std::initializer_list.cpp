#include <bits/stdc++.h>
#include <string>
#include <string_view>


namespace Kai {
    template <typename T>
    class initializer_list {
        private:
        T const* data_;
        std::size_t len_;
        public:
        initializer_list(T *const data, std::size_t size) {
            data_ = data;
            len_ = size;
        }
        T const* begin() const {
            return data_;
        }

        T const* end() const {
            return data_ + len_;
        }
    };

    void foo(initializer_list<int>& list) {
        std::cout << "Inside foo!\n";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << '\n';
        }

    }
}



int main() {

    // std::initializer list ? 
    int arr[2] = {1, 2};
    Kai::initializer_list<int> list = {arr, 2};
    Kai::foo(list);

    return 0;
}
