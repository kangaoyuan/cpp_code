#include <list>
#include <vector>
#include <iostream>
#include <iterator>
#include <type_traits>

template <typename Iterator>
Iterator next(Iterator iter, size_t n){
    if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>){
        return iter + n; 
    } else {
        for(size_t i = 0; i < n; ++i){
            ++iter; 
        } 
        return iter;
    }
}

int main(){
    std::vector<double> vec = {5.7, 6.7, 7.7, 2.7};
    std::list lst{1.2, 2.3, 4.5, 6.7, 7.8};

    // can use gdb to find the difference or add print or log.
    std::cout << *next(vec.begin(), 2) << std::endl;
    std::cout << *next(lst.begin(), 2) << std::endl;
}
