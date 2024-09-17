//
// Created by Lin Kai on 17/9/24.
//

#ifndef CPPDUMP_STRING_H
#define CPPDUMP_STRING_H


#include <iostream>
#include <memory>
#include <cstring>

// shared_ptr
// string ?
// malloc

struct MyString {
    char* data_;
    char buffer[15];
    size_t length = 0;
    MyString(char* ptr_) {
        length = strlen(ptr_);
        std::cout << "Length is " << length << '\n';
        data_ = new char[length + 1]; // for the nummptr at the back
        strcpy(data_, ptr_);
    }

    size_t size() const {
        return length + 1;
    }

    friend std::ostream& operator << (std::ostream& os, const MyString& point) {
        os << point.data_ << '\n';
        return os;  // Return the ostream object to allow chaining (e.g., std::cout << point1 << point2)
    }

    ~MyString () {
        delete[] data_;

    }

};


int main() {
    MyString s("Hello");
    std::cout << s << '\n';
    return 0;
}


#endif //CPPDUMP_STRING_H
