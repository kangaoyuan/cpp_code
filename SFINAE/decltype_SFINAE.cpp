#include <utility>
#include <iostream>
#include "customer_class.h"


template<typename T>
struct has_serialize{
    template<typename U>
    static constexpr auto test(U* p) ->decltype(std::declval<U&>().serialize(), bool()) {
        return true; 
    }
    
    template<typename U>
    static constexpr auto test(...) {
        return false; 
    }

    static constexpr bool value = test<T>(nullptr);
};

// Aka variable template.
template<typename T>
constexpr bool has_serialize_v = has_serialize<T>::value;

int main(){
    std::cout << std::boolalpha;
    std::cout << has_serialize_v<A> << std::endl;
    std::cout << has_serialize_v<B> << std::endl;
    std::cout << has_serialize_v<C> << std::endl;
}
