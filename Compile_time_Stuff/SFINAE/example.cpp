//
// Created by Lin Kai on 20/9/24.
//

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <thread>
#include <iostream>
#include <memory>
#include <algorithm>


template <typename T, std::size_t N>
std::size_t len(T(&A)[N]) {
    std::cout << "First\n";
    return N;
}

template <typename T>
typename T::size_type len( T const& t) {
    std::cout << "second\n";
    return t.size();
}

// instead of reporting ambiguous or reporting an error, that not matching template
// is just removed.


int main() {
    int a[10];
    std::cout << len(a) << '\n';
    std::cout << len("tmp") << '\n';
    std::vector<int>V;
    std::cout << len(V);


    return 0;
}