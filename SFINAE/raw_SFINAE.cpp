#include <vector>
#include <iostream>
#include "customer_class.h"

// other method to not explicit specify the template argument, using a function template parameter to deduct the template argument. For example:
void func(...){}

template<typename U>
void func(const U& t, typename U::iterator* it = nullptr){
    // Don't put the constraints in function body.
}


template<typename T>
class has_reserve {
private:
    template<typename U, void(U::*)(size_t)>
    class SFINAE{};
    template<typename U, U u>
    class _SFINAE{};
public:
    template<typename U>
    constexpr static bool test(...) { return false; }
    template<typename U>
    constexpr static bool test(SFINAE<U, &U::reserve>* ptr) { return true; }

    template<typename U>
    constexpr static bool _test(_SFINAE<long long (U::*)() const, &U::serialize>* ptr){
        return true; 
    }
    template<typename U>
    constexpr static bool _test(_SFINAE<long long (U::*)(), &U::serialize>* ptr){
        return true; 
    }
    template<typename U>
    constexpr static bool _test(...){
        return false; 
    }


    constexpr static bool value = test<T>(nullptr);
    constexpr static bool _value = _test<T>(nullptr);
};

template<typename T>
constexpr bool has_reserve_v = has_reserve<T>::value;

template<typename T>
constexpr bool has_serialize_v = has_reserve<T>::_value;

int main(){
    std::cout << std::boolalpha;

    std::cout << has_reserve_v<int> << std::endl;
    std::cout << has_reserve_v<std::vector<int>> << std::endl;

    std::cout << has_serialize_v<A> << std::endl;
    std::cout << has_serialize_v<B> << std::endl;
}
