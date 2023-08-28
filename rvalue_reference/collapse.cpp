#include <iostream>
#include <boost/type_index.hpp>
#define Log() (std::cout << __FILE__ << " : " << __LINE__ << " : " << __PRETTY_FUNCTION__ << std::endl)
using namespace boost::typeindex;

template<typename T>
void foo(T&& param) {
    Log();
    std::cout << "T type is: " << type_id_with_cvr<T>() << std::endl; 
    std::cout << "T& type is: " << type_id_with_cvr<T&>() << std::endl; 
    std::cout << "T&& type is: " << type_id_with_cvr<T&&>() << std::endl; 
    std::cout << "param type is: " << type_id_with_cvr<decltype(param)>() << std::endl; 
}

int main(){
    int x;
    int &ref1 = x;
    int &&ref2 = 77;

    foo(x);
    std::cout << "=============================================" << std::endl;
    foo(77);
    std::cout << "=============================================" << std::endl;
    foo(ref1);
    std::cout << "=============================================" << std::endl;
    foo(ref2);
    std::cout << "=============================================" << std::endl;
    foo(std::forward<int>(ref1));
    std::cout << "=============================================" << std::endl;
    foo(std::forward<int>(ref2));
    std::cout << "=============================================" << std::endl;
    foo(std::forward<int&>(ref1));
    std::cout << "=============================================" << std::endl;
    foo(std::forward<int&>(ref2));
    std::cout << "=============================================" << std::endl;
    foo(std::forward<int&&>(ref1));
    std::cout << "=============================================" << std::endl;
    foo(std::forward<int&&>(ref2));
    std::cout << "=============================================" << std::endl;
    return 0;
}
