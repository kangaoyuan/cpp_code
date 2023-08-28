#include <array>
#include <iostream>


struct Foo: std::true_type{};

int sqr(int n) { 
    return n * n; 
}

constexpr int sqr_(int n) { 
    return n * n; 
}

constexpr int factorial(int n) {
    /* Because constexpr functions can be apply at run-time, so we can't diretly apply static_assert in constexpr functions */
    // static_assert(n >= 0, "");         //error
    if (n < 0) {
        throw std::invalid_argument("Arg must be non-negative");
    }

    return n == 0 ? 1 : n * factorial(n - 1);
}

void test(){
    constexpr bool foo = Foo{};
    constexpr bool foo_ = Foo::value;
    constexpr std::string_view sv{"hi"};
    constexpr std::pair pr{sv[0], sv[1]};
    constexpr std::array arr{pr.first, pr.second};

    auto func = [](int a, int b) constexpr {
        return a + b; 
    };

    static_assert(Foo(), "class member functions can be executed at compile time");
    static_assert(func(1, 2) == 3, "lambda call can be executed at compile time");
}

int main() {
    test();

    int a[sqr(3)];                      // ok, C VLA arrays 
    const int n1 = sqr(3);              // ok, const variable not guaranteeing
    const int n2 = sqr_(3);             // compile-time, but can do it.

    //constexpr int n3 = sqr(3); // error, normal function can't do it.
    constexpr int n3 = sqr_(3); // constexpr=constant expression 常量表达式

    std::array<int, n2> aa;     // ok, verifying the const variable.
    std::array<int, factorial(5)> b; // ok, constexpr function.
    return 0;
}
