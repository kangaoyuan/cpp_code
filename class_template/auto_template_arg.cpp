#include <iterator>
#include <iostream>
#include <algorithm>

//template<typename T>
/* too many, wrong number of template arguments */
// template<typename U, typename V>
/* the defualt template argument, can be ignored or not ignored */
template<typename U, typename V = void>
struct DataMemPtr{};

// for class template specialization, it can be used for class deduction, and the template argumentes are not limitation for template specialization.
template<typename DataType_, typename ClassType_>
struct DataMemPtr<DataType_ (ClassType_::*)>{
    using DataType = DataType_;
    using ClassType = ClassType_;
};

// auto in template parameter list is used to declare Non-type template argument, which can be used in class template or function template.
template<auto Ptr>
const typename DataMemPtr<decltype(Ptr)>::DataType&
getter(const typename DataMemPtr<decltype(Ptr)>::ClassType& obj){
    return obj.*Ptr; 
}

struct X{
    int a;
    double b;
};

int main(){
    X arr[] = { {1, 2.3}, {4, 5.6}, {7, 8.9} };

    std::cout << "int:" << std::endl;
    std::transform(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "), getter<&X::a>);
    std::cout << std::endl;

    std::cout << "double:" << std::endl;
    std::transform(std::begin(arr), std::end(arr), std::ostream_iterator<double>(std::cout, " "), getter<&X::b>);
    std::cout << std::endl;
    
    return 0;
}
