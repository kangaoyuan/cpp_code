#include <memory>
#include <iostream>
#include <iterator>

template<typename T, typename U>
class Test{
public:
    // On the body of class template, We should distinguish the class template
    // parameters and the function template parameters. Only the function
    // template parameter can represent the universal reference.
    template<typename V, typename W>
    Test(T t, U&& u, V&&, W){}
};
template<typename T, typename U>
class Example{
public:
    Example(T t, U u) { std::cout << "Example(T t, U u)" << std::endl; }
    Example(T t, U u, const char* str) { std::cout << "Example(T t, U u, const char* str)" << std::endl; }
};

template<typename T>
class Example<T, long long>{
public:
    Example(T t, int val) { std::cout << "Example(T t, int val)" << std::endl; }
    Example(T t, int val, double str) { std::cout << "Example(T t, int val, double str)" << std::endl; }
};

template<typename T, typename Allocator = std::allocator<T>>
class My_Vector{
public:
    class iterator{
        using pointer = T*;
        using reference = T&;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using iterator_category_tag = std::random_access_iterator_tag;
        //...
    };

    My_Vector(iterator begin, iterator end);
    //...
};

template <typename Iterator>
My_Vector(Iterator begin, Iterator end)
    -> My_Vector<typename std::iterator_traits<Iterator>::value_type>;

int main(){
    Example x(1, 2.0);
    Example y(1, 2.0, "hello");
    /* error 
     * class template argument deduction only occured on constructors,
     * but not including class template specialization constructors */
    //Example t1(1, 2, 7.7);
    Example<int, long long> t1(1, 2, 7.7);
    Example<int, long long> t2(1, 2ll);
    /* error
     * Although class tmeplate only use non-specializatin version constructors
     * to deduct type template argument, but only the most matching class 
     * template's constructor will be applied.*/
    //Example t3(1, 2ll, "hello");
    Example t4(1, 2ll);

    return 0;
}
