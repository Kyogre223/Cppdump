//
// Created by Lin Kai on 9/10/24.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>



struct obj {
    obj(int a, int b):x{a}, y{b} {
        valid = true;
    }
    int x;
    int y;
    bool valid;
};

template <typename T>
void defragment(std::vector<T*>& A, void* buffer) {
    int sz = sizeof(T);
    // since I have to maintain the original order of the pointers, just copy one out?

    std::vector<T*> B = A;
    std::sort(B.begin(), B.end(), [](auto a, auto b) { return a < b; });
    std::vector<T> B_items;
    B_items.reserve(A.size());

    // copy them out here, to take into consideration of the overlapping
    // can we use memmove here then?
    for (auto const& item : B) {
        B_items.push_back(*item);
        std::cout << "copying\n";
        std::cout << item->x << ' ' << item->y << '\n';
    }
    char* ptr = static_cast<char*>(buffer);
    for (int i = 0; i < A.size(); ++i) {
        std::cout << "Current ptr address: " << static_cast<void*>(ptr) << '\n';
        T* temp = reinterpret_cast<T*>(ptr);
        *temp = B_items[i];
        ptr += sizeof(T);
    }
}

template <typename T>
void print(void* ptr) {
    std::cout << reinterpret_cast<T*>(ptr)->x << ' ' << reinterpret_cast<T*>(ptr)->y << ' ' << reinterpret_cast<T*>(ptr)->valid << '\n';
}
int main() {

    char BUFFER[sizeof(obj) * 1024];
    obj* obj1 = new (&BUFFER[0]) obj{2, 3};
    obj* obj2 = new (&BUFFER[0 + sizeof(obj)]) obj{4, 5};
    obj* obj3 = new (&BUFFER[0 + sizeof(obj)* 10]) obj{7, 10};
    std::cout << "Address are:\n";
    std::cout << obj1 << ' ' << obj2 << ' ' << obj3 << '\n';

    std::vector<obj*>vec = {obj1, obj3, obj2};

    defragment<obj>(vec, BUFFER);
    std::cout << "Checking....\n";
    print<obj>(&BUFFER[0]);
    print<obj>(&BUFFER[sizeof(obj)]);
    print<obj>(&BUFFER[sizeof(obj) * 2]);
    return 0;
}
