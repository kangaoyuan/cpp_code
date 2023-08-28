#include <array>
#include <iostream>
#include <boost/core/demangle.hpp>
#include <boost/type_index.hpp>

using boost::core::demangle;
using namespace boost::typeindex;

//typedef char arr[42];
using arr = char [42];
//using arr = char (&)[42];

typedef char yes; // Size: 1 byte.
typedef yes no[2]; // Size: 2 bytes.

// Three functions using our custom type with different size as return type.
yes f1() {
    char tmp;
    return  tmp;
}

/* Can't return an array from function */
//no f2() {
no& f2() {
   auto* ptr = new char[2]; 
   // can't use static_cast<>()
   return *reinterpret_cast<char (*)[2]>(ptr);
}

arr& f(){
    std::cout << "In function body, it be executed." << std::endl;
    auto* ptr = new char[42];
    return reinterpret_cast<char (&)[42]>(*ptr);
}

int main(){
    // The expression in sizeof(), which won't actually executed.
    char array__[sizeof(f())];
    std::array<int , sizeof(f())> array_;
    std::cout << sizeof(f()) << std::endl;
    std::cout << sizeof(f1()) << std::endl;
    std::cout << sizeof(f2()) << std::endl;

    /* array must be initialize with a brace-enclosed initializer list */
    //arr mem = f();
    arr& mem = f();
    mem[0] = 'x';
    mem[41] = 'y';
    no& tmp = f2();
    tmp[0] = 'a';
    tmp[1] = 'b';

    std::cout << demangle(typeid(arr).name()) << std::endl;
    std::cout << demangle(typeid(arr&).name()) << std::endl;
    std::cout << demangle(typeid(f()).name()) << std::endl;
    std::cout << demangle(typeid(mem).name()) << std::endl;
    std::cout << type_id_with_cvr<arr>() << std::endl;
    std::cout << type_id_with_cvr<arr&>() << std::endl;
    std::cout << type_id_with_cvr<decltype(f())>() << std::endl;
    std::cout << type_id_with_cvr<decltype(mem)>() << std::endl;
    std::cout << demangle(typeid(f2()).name()) << std::endl;
    std::cout << demangle(typeid(tmp).name()) << std::endl;
    delete[] &mem;
    delete[] &tmp;
    std::cout << "final" << std::endl;
    return 0;
}
