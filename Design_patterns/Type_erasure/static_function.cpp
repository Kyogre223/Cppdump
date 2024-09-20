#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <thread>
#include <iostream>
#include <memory>
#include <algorithm>

// implementation 2

template <typename T>
struct MyFunction;


template <typename Ret, typename... Args>
struct MyFunction<Ret(Args...)> {
    template <typename T>
    static void helper(void* ptr, Args... args) {
        (*static_cast<T*>(ptr))(args...);
    }

    template <typename I>
    static void test() {
        std::cout << "Hello\n";
    }

    template <typename T>
    static void helper2(void* ptr) {
        delete (static_cast<T*>(ptr));
    }

    MyFunction(Ret(*f)(Args...)): obj_(new decltype(f){}), ptr_(helper<decltype(f)>), dtor_(helper2<decltype(f)>){

    }

    ~MyFunction() {
        dtor_(obj_);
    }

    Ret operator () (Args... args) {
        return ptr_(obj_, args...);
    }

    void* obj_;
    void(*ptr_)(void*, Args...);
    void(*dtor_)(void*);
};

void foo(int a, int b) {
    std::cout << a + b << '\n';
    return;
}




int main() {
    MyFunction<void(int, int)>f = foo;
    foo(2, 4);
    MyFunction<void(int, int)>::template test<int>();


    return 0;
}