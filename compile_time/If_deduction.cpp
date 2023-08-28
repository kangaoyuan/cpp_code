#include <iostream>

template<bool cond, typename Then, typename Else> 
struct If;

template<typename Then, typename Else>
struct If<true, Then, Else>{
    using result = Then;
};


template<typename Then, typename Else>
struct If<false, Then, Else>{
    using result = Else;
};

template<int N>
struct isEven {
    static constexpr auto result = If<(N & 1) == 0, std::true_type, std::false_type>::result::value;
};

template<int Num1, int Num2>
struct Add{
    static constexpr auto value = Num1 + Num2;
};

template<int Num1, int Num2>
struct Sub{
    static constexpr auto value = Num1 - Num2;
};

template<int Num, int Num1, int Num2>
struct Add_Sub{
    static constexpr auto result = If<isEven<Num>::result, Add<Num1, Num2>, Sub<Num1, Num2>>::result::value;
};

int main() {
    std::cout << std::boolalpha;

    std::cout << isEven<19>::result << std::endl;
    std::cout << isEven<88>::result << std::endl;

    std::cout << Add_Sub<77, 77, 27>::result << std::endl;
    std::cout << Add_Sub<88, 27, 77>::result << std::endl;
}
