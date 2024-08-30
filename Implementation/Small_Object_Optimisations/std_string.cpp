//
// Created by Lin Kai on 30/8/24.
//


#include <iostream>
#include <cstring>
#include <string>

// local buffer optimisation


// I guess you know the part of about shared_ptrs ? maybe we can talk about strings and queues.
// strings have a small buffer internally.


// queues are, circular buffers.

// lets try implementing with a string

// without small string optimisation
struct myString {
    // MY SMALL BUFFER XD
    char buf[16];
    char* ptr_ = nullptr;
    int capacity = 0;
    int size = 0;
    myString(char const* ptr):ptr_(new char[strlen(ptr) + 1]){
        std::cout << strlen(ptr) << '\n';
        std::cout << "constructed!\n";
        strcpy(ptr_, ptr);
        this->size = strlen(ptr);
        this->capacity = strlen(ptr);
        std::cout << ptr_ << '\n';
    }

    // copy constructor
    myString(myString const& other) {
        // small string logic applied here
        if (strlen(other.ptr_) <= sizeof(buf)) {
            strcpy(buf, other.ptr_);
            ptr_ = buf;
            return;
        }
        ptr_ = new char[strlen(other.ptr_) + 1];
        strcpy(ptr_, other.ptr_);
        std::cout << "OTHER " << strlen(ptr_) << '\n';
        this->size = other.size;
        this->capacity = other.capacity;
    }


    ~myString() {
        std::cout << "destructed!\n";
        if (ptr_ != nullptr) {
            delete[] ptr_;
        }
    }
};
int main() {

    myString s = "Hello";
    myString s2 = s;


    return 0;
}