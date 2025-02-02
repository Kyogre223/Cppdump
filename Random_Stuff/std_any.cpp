#include <iostream>
#include <memory>

class MyAny {
public:
    template <typename T>
    MyAny(T data): data_(std::make_unique<Child<T>>(data)) {}

    class Base {
    public:
        Base() = default;
        virtual ~Base() = default;
    };

    template <typename T>
    class Child : public Base {
    public:
        Child(T data) : obj(data) {}

        T obj;
    };

    template <typename T>
    T* get() {
        auto* derived = dynamic_cast<Child<T>*>(data_.get());
        return derived ? &derived->obj : nullptr;
    }

private:
    std::unique_ptr<Base> data_;
};

int main() {
    MyAny i(5);

    int* value = i.get<int>();
    if (value) {
        std::cout << *value << '\n';
    } else {
        std::cout << "Type mismatch or null value\n";
    }
    return 0;
}
