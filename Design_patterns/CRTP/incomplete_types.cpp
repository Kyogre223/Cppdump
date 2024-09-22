//
// Created by Lin Kai on 22/9/24.
//


template <typename D>
class B {
    using Y = typename D::T; // does not compile, D is an incomplete type!
};

class D: public B<D> {
    using T = int;
};