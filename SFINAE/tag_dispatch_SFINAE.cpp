#include <iostream>
#include <type_traits>
#include "customer_class.h"

/* Attention, the class template argument number should be two. */
template<typename T,  typename = void>
struct has_serialize: public std::false_type{};

/* struct by default is public inheritance */
template<typename T>
struct has_serialize<T, std::void_t<decltype(std::declval<T&>().serialize())>>: std::true_type{};

template<typename T>
/* One type inheriting true_type or false_type, which has a constexpr operator bool() conversion member function */
//constexpr bool has_serialize_v = has_serialize<T>{};
/* true_type or false_type has a constexpr static bool data member*/
constexpr bool has_serialize_v = has_serialize<T>::value;

int main(){
    std::cout << std::boolalpha;
    std::cout << has_serialize<A>() << std::endl;
    std::cout << has_serialize<B>() << std::endl;
    std::cout << has_serialize<C>() << std::endl;
}
