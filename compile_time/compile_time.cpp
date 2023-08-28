#include <iostream>
#include <stdexcept>

/* static const or static constexpr data member in class template to indicate compile-time value. */
template<int N>
struct factorial_1{
    static_assert(N >= 0, "struct factorial_1 non-type template parameter must be non-negative");
    /* Here static const int is also correct */
    // static const int value = N * factorial_1<N-1>::value;
    /* static constexpr int is default inline */
    static constexpr int value = N * factorial_1<N-1>::value;
};

// Full specialization
template<>
struct factorial_1<0>{
    /* Here static const int is also correct */
    // static const int value = 1;
    static constexpr int value = 1;
};


/* constexpr function to reflect compile-time value */
constexpr int factorial_2(int n){
    // Here constexpr function can't guarantee always execute at the compile-time, so we can't use static_assert() and use throw; exception.
    if(n < 0)
        throw std::runtime_error("factorial parameter need non-negative value");
    return n > 0 ? n * factorial_2(n -1) : 1;
    //if(!n) 
    //    return 1;
    //return n * factorial_2(n-1); 
}

int main(){
    std::cout << "factorial_1<7>::value == " << factorial_1<7>::value << std::endl;
    std::cout << "factorial_2<7>::value == " << factorial_2(7) << std::endl;
    return 0;
}
