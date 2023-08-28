#include <array>
#include <iostream>

class Example{
public:
     static const int x = 7;
};

/* whatever if define static const int data member outside class body, it's an compile-time constant(constexpr variable), but defining outside class will allocate the memory space.*/
//const int Example::x = 7;

int main(){
    //std::cout << &Example::x << std::endl;
    /* When definiting the static const data member outside class body, we can address of it. But it can still used as compile-time constant */
    std::array<double, Example::x> arr = {2, 4, 6, 8};
    std::cout << "arr: ";
    for(const auto& elem: arr){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;
    return 0;
}
