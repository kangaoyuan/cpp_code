#include <iostream>

// overload functin
int mg_gcd(int a, int b){
    std::cout << "In int mg_gcd(int, int); func signature" << std::endl;
    while(b != 0){
        int r = a % b;
        a = b;
        b = r; 
    }
    return a;
}

// function template
template<typename T>
T mg_gcd(T a, T b){
    std::cout << "In T mg_gcd(T, T); func template signature" << std::endl;
    while(b != T{0}){
        T r = a % b;
        a = b;
        b = r; 
    }
    return a;
}

// explicit instantiation
template
long long mg_gcd(long long, long long);

// extern instantiation
extern template
unsigned long long mg_gcd(unsigned long long, unsigned long long);

