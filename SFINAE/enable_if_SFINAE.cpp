#include <ios>
#include <iostream>
#include <type_traits>
#include "customer_class.h"

template<typename T>
std::enable_if_t<std::is_same_v<decltype(std::declval<T&>().serialize()), long long>, bool> 
test(){
    return true;
}

template<typename T>
std::enable_if_t<!std::is_same_v<decltype(std::declval<T&>().serialize()), long long>, bool> test(){
    return false;
}
int main(){
    std::cout << std::boolalpha;
    std::cout << test<A>() << std::endl;
    return 0;
}
