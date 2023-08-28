#include <iterator>
#include <iostream>
#include <algorithm>

/* Below template parameter list is wrong. becauses function template iteself
 * function parameter list is not been known for template parameter list. 
 * Maybe the function parameter list is for instantiation.*/
//template<typename DataType, DataType ClassType::* Ptr>
template<typename DataType, typename ClassType, DataType ClassType::* Ptr>
DataType getter(const ClassType& obj){
    return obj.*Ptr;
}

struct X{
    int a;
    double b;
};

int main(){
    X arr[] = { {1, 2.3}, {4, 5.6}, {7, 8.9} };

    std::cout << "int:" << std::endl;
    std::transform(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "), getter<int, X, &X::a>);
    std::cout << std::endl;

    std::cout << "double:" << std::endl;
    std::transform(std::begin(arr), std::end(arr), std::ostream_iterator<double>(std::cout, " "), getter<double, X, &X::b>);
    std::cout << std::endl;

    return 0;
}
