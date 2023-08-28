#include <iostream>
#include "shape.h"
#include "smart_ptr.h"

int main(){
    shared_ptr<circle> ptr1(new circle());
    std::cout << "use count of ptr1 is " << ptr1.get_count() << std::endl;
    shared_ptr<shape> ptr2;
    shared_ptr<shape> ptr3;
    std::cout << "use count of ptr2 is " << ptr2.get_count() << std::endl;
    std::cout << "use count of ptr3 is " << ptr3.get_count() << std::endl;
    ptr2 = ptr1;        
    ptr3 = ptr1;
    std::cout << "use count of ptr1 is now " << ptr1.get_count() << std::endl;
    std::cout << "use count of ptr2 is now " << ptr2.get_count() << std::endl;
    std::cout << "use count of ptr3 is now " << ptr3.get_count() << std::endl;
    if (ptr1) {
        std::cout << "ptr1 is not empty" << std::endl;
    }
    ptr2 = std::move(ptr1);
    if (!ptr1 && ptr2) {      
        std::cout << "ptr1 move to ptr2" << std::endl;
        std::cout << "use count of ptr1 is now " << ptr1.get_count() << std::endl;
        std::cout << "use count of ptr2 is now " << ptr2.get_count() << std::endl;
        std::cout << "use count of ptr3 is now " << ptr3.get_count() << std::endl;
    }
}
