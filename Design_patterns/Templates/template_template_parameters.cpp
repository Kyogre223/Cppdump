//
// Created by Lin Kai on 24/9/24.
//

#include <iostream>
#include <vector>
#include <string>

// // template template parameters.
template <typename T, template <typename> typename Container>
class Builder {
    Container<T> data_;
public:
    void add(T const& t) {data_.push_back(t);}
    void print() const {
        for (auto const& d : data_) {
            std::cout << d << ' ';
        }
        std::cout << "\n";
    }
};

template <template <typename> typename Out_container,
        template <typename> typename In_container,
        typename T>
Out_container<T> resequence(In_container<T> const& in_container) {
    Out_container<T> out_container;
    for (auto x : in_container) {
        out_container.push_back(x);
    }
    return out_container;
}



int main() {
    Builder<int, std::vector>B;
    B.add(10);
    B.add(20);

    return 0;
}