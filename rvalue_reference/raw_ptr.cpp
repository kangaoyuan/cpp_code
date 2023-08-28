#include <iostream>
#include "shape.h"
#include "auto_ptr.h"

int main(){
    auto_ptr<shape> ptr1{create_shape(shape_type::circle)}; 
    auto_ptr<shape> ptr2{ptr1};

    // using opertor bool(); conversion member function
    if(!ptr1 && ptr2){
        std::cout << "auto_ptr<> copy constructor: clear the rhs, storing in the lhs" << std::endl; 
    }
    ptr1.reset();

    auto_ptr<shape> ptr3{create_shape(shape_type::triangle)};
    ptr1 = ptr3;
    if(ptr1 && !ptr3){
        std::cout << "auto_ptr<> operator=(auto_ptr tmp): clear the rhs, storing in the lhs" << std::endl; 
    }

    return 0;
}
