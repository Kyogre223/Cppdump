namespace detail {

    class Base {
        public:
        virtual void operate() const = 0;
        virtual std::unique_ptr<Base> clone() = 0;
        virtual ~Base() = default;
    };


    template <typename T, typename U>
    class Child : public Base {
        explicit Child(T data, U func):data_(std::move(data)), func_(std::move(func)){
        }
        void operate() const override {
            func_(data_);
        }
        std::unique_ptr<Base> clone() {
            return std::make_unique<Child>(*this);
        }

        private:
        T data_;
        U func_;
    };
}

class A {
    public:
    template <typename T, typename U>
    explicit A(T data_, U func_) {
        using Child = detail::Child<T, U>;

        data_ = std::make_unique<Child>(data_, func_);
    }

// copy ctr
    A(A const& other) {
        data_ = other.data_->clone();
    }
// move ctr
    A(A&& other) {
        data_.swap(other.data_);
    }
// copy assignment
    A& operator = (A const& other) {
        A cpy = other;
        // Copy and swap
        data_.swap(cpy.data_);

        return *this;
    }

    // move assignment 
    A& operator = (A&& other) {
        data_.swap(other.data_);
        return *this;
    }







    private:
    friend void operate(A const& a) {
        a.data_->operate();
    }
    std::unique_ptr<detail::Base>data_;
    
};
