#include <array>
#include <iostream>

inline constexpr int size =5;

constexpr int fib(int n){
    // in c++11, the constexpr functions only have one return statement.
    // but later c++ standard, the constexpr functions have more functionality
    int a = 0;
    int b = 1;
    for (int i = 0; i < n; ++i) {
        int c = a + b;
        a = b;
        b = c;
    }
    return a;
}

void test() {
    auto func = [](double a, double b) constexpr{
        return a + b; 
    };

    /* if lambda expression meets the requirements of constexpr function, we can ignore constexpr keyword */ 
    //auto fib = [](int n) ->int {
    auto fib = [](int n) constexpr ->int {
        int a = 0;
        int b = 1;
        for (int i = 0; i < n; ++i) {
            int c = a + b;
            a = b;
            b = c;
        }
        return a;
    };

    static_assert(fib(5) == 5, "");
    static_assert(fib(6) == 8, "");
    static_assert(func(2, 3) == 5, "lambda expression can be marked as constexpr");
}

class Rect{
public:
    // when constexpr keyword acts on constructor, it can generate a compile-time object.
    constexpr Rect(double length, double width): m_length(length), m_width(width){};

    constexpr auto get_area() const {
        return m_length * m_width; 
    }

private:
    double m_length = {};
    double m_width = {};
};

constexpr int when_run(int x, int a, int b){
    auto f = [x](int y) constexpr {
        return x * y; 
    };
    return f(a) + f(b);
}

int main(){
    static_assert(size == 5, "");
    std::array<double, size> arr1;

    static_assert(fib(6) == 8, "");
    std::array<double, fib(6)> arr2;

    int runtime_input;
    std::cout << "input a number as argument to fib(): ";
    if (std::cin >> runtime_input) {
        /* constexpr function can be executed at run-time */
        std::cout << fib(runtime_input) << std::endl;
    }

    test();
    static_assert(Rect(3, 5).get_area() == 15, "");

    static_assert(when_run(2, 3, 4) == 14, "");
    static_assert(when_run(3, 4, 5) == 27, "");

    int a, b, c;
    std:: cout << "input x, y, z number, evaluating x * (y + z):";
    std::cin >> a >> b >> c;
    // triggering compile-time error
    std::cout << when_run(a, b, c) << std::endl;
}
