#include <array>
#include <iostream>

struct magic{
    static const int number = {7};
    /* The static constexpr class data members, which must be integral types, defined in class definition body default are inline attributes */
    static constexpr int number_ = {7};
};

/* The static const class data member exception integral types must define outside class definition. */
//const int magic::number = 7;

int main(){
    //int arr1[magic::number] = {1, 3, 5, 7};
    std::array<int, magic::number> arr1 = {1, 3, 5, 7};
    std::cout << "arr1: ";
    for(const auto& elem : arr1){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;

    /* if `const int var = ` is initialized by constexpr at compile-time, itself is also a compile-time constexpr. */
    const int index = 7;
    const int num1 = magic::number;
    //int arr2[index] = {2, 4, 6, 8};
    std::array<int, index> arr2 = {2, 4, 6, 8};
    std::cout << "arr2: ";
    for(const auto& elem : arr2){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;

    std::array<int, num1> arr3 = {9, 8, 7, 6};
    //int arr3[num1] = {9, 8, 7, 6};
    std::cout << "arr3: ";
    for(const auto& elem : arr3){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;

    return 0;
}
