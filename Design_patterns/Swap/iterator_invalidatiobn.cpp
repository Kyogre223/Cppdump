//
// Created by Lin Kai on 22/9/24.
//

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

int main() {


    std::vector<int>V1 = {1, 2 , 3 , 4};
    std::vector<int>V2 = {2, 3, 4 , 5};
    auto it1 = V1.begin();
    auto it2 = V2.begin();
    V1.swap(V2);
    std::cout << *it1 << '\n';
    std::cout << *it2 << '\n';



    return 0;
}

// jokes, iterator is still valid LOL
