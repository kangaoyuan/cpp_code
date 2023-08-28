#include <iostream>

template<int N, auto... Xs>
struct nth_value{};

template<int N, auto X0, auto... Xs>
struct nth_value<N, X0, Xs...>{
    static_assert(N > 0 && N <= sizeof...(Xs), "index error");
    static constexpr auto value = nth_value<N-1, Xs...>::value;
};

template<auto X0, auto... Xs>
struct nth_value<0, X0, Xs...>{
    static constexpr auto value = X0;
};

/* next statement is error, because pointer is wrong, which is different from
 * char array !!! */
//static constexpr auto str = "abc";
static constexpr char str[] = "xyz";

template<auto... Xs>
struct values_list{
    template<int N>
    using get = nth_value<N, Xs...>;
};

template<int N, auto... Xs>
static constexpr auto nth_value_v = nth_value<N, Xs...>::value;

int main(){
    std::cout << nth_value<0, 7, str, 'c'>::value << std::endl;
    std::cout << nth_value<1, 7, str, 'c'>::value << std::endl;
    std::cout << nth_value<2, 7, str, 'c'>::value << std::endl;

    std::cout << nth_value_v<0, 7, str, 'c'> << std::endl;
    std::cout << nth_value_v<1, 7, str, 'c'> << std::endl;
    std::cout << nth_value_v<2, 7, str, 'c'> << std::endl;
    return 0;
}
