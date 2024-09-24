//
// Created by Lin Kai on 24/9/24.
//


template <typename T>
constexpr T pi = 3.141412312312312312312312312312423523445;


int main() {
    std::cout << pi<int> << '\n';
    std::cout << pi<float> << '\n';
    std::cout << pi<double> << '\n';


    return 0;
}