//
// Created by Lin Kai on 20/9/24.
//


template <typename T>
struct MyFunction;


template <typename Ret, typename... Args>
struct MyFunction<Ret(Args...)> {
    MyFunction(Ret(*f)(Args...)):storage_(std::make_unique<Child<decltype(f)>>(f)){}

    Ret operator () (Args... args) {
        return storage_->call(args...);
    }

    struct Base {
        virtual Ret call (Args...) = 0;
        virtual ~Base() {}

    };

    template <typename T>
    struct Child: Base {
        Child(T data): data_(data){}
        Ret call (Args... args) override {
            return data_(args...);
        }

        T data_;
    };


    std::unique_ptr<Base>storage_;
};

void foo(int a, int b) {
    std::cout << a + b << '\n';
    return;
}

int main() {
    // int a, b, c; // grows from higher to lower
    // std::cout << &a << '\n';
    // std::cout << &b << '\n';
    // std::cout << &c << '\n';
    MyFunction<void(int, int)>f = foo;
    f(2, 4);

    return 0;
}