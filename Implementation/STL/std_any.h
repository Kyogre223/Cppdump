//
// Created by Lin Kai on 25/8/24.
//

#ifndef CPPDUMP_STD_ANY_H
#define CPPDUMP_STD_ANY_H


// abit lazy to finish and touch up....
struct MyAny {

    template <typename T>
    MyAny(T data): info_(typeid(T)), data_{std::make_unique<child<T>>(data)}{}

    template <typename T>
    MyAny& operator = (T data) {
        data_.reset();
        data_ = std::make_unique<child<T>>(data);
        return *this;

    }

    struct base {
        base() = default;
        virtual ~base() = default;
    };

    template <typename T>
    struct child: base {
        child(T data): handler_{data}{}
        ~child() = default;
        T getData() const {
            return handler_;
        }

        std::type_info const& getType() const {
            return typeid(handler_);
        }
        T handler_;
    };

    template <typename T>
    friend T MyAnyCast(MyAny& any) {
        if (any.info_ != typeid(T)) {
            throw std::bad_any_cast();
        }
        return static_cast<child<T>*>(any.data_.get())->getData();
    }

    std::type_info const& type() const {
        return info_;
    }


    std::type_info const& info_; // make this into a lambda first
    std::unique_ptr<base>data_;
};


#endif //CPPDUMP_STD_ANY_H
