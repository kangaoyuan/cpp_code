#include <iostream>

template<bool cond, typename Body>
struct WhileLoop;

template<typename Body>
struct WhileLoop<false, Body> {
    using type = typename Body::result_type;
};

template<typename Body>
struct WhileLoop<true, Body> {
    using type  = typename WhileLoop<Body::cond, typename Body::next_type>::type;
};

template<typename Body>
using While_t = typename WhileLoop<Body::cond, Body>::type;

template<typename T, T Val>
struct integral_constant {
    using value_type = T;
    using type = integral_constant<T, Val>;
    constexpr static T value = Val;
};

template<int Val, int Result> 
struct Sum {
    constexpr static bool cond = Val != 0;

    using result_type = integral_constant<int, Result>;
    using next_type = Sum<Val -1, Result + Val>;
};

int main(){
    std::cout << While_t<Sum<6, 0>>::value << std::endl;
    return 0;
}
