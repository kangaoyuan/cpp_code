#include <iostream>
#include "shape.h"

result process_shape(const shape& shape1, const shape& shape2){
    puts("process_shape()");
    result tmp;
    return tmp;
}

int main(){
    puts("begin main()");
    process_shape(circle(), triangle());
    std::cout << "=======prvalue can be extended for rvalue reference=======" << std::endl;
    result&& extension = process_shape(circle(), triangle());
    std::cout << "=======xvalue can't be extended for rvalue reference=======" << std::endl;
    result&& failure_extension = std::move(process_shape(circle(), triangle()));
    puts("end main()");
}
