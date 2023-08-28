#include <list>
#include <vector>
#include <iterator>
#include <iostream>

namespace impl {

template <typename Category>
class Helper{
public:
    template <typename Iterator>
    static Iterator next(Iterator iter, size_t n){
        for(size_t i = 0; i < n; ++i){
            ++iter; 
        }
        //std::cout << __PRETTY_FUNCTION__ << std::endl;
        return iter;
    }
};

template <>
class Helper<std::random_access_iterator_tag>{
public:
    template <typename Iterator>
    static Iterator next(Iterator iter, size_t n){
        //std::cout << __PRETTY_FUNCTION__ << std::endl;
        return iter + n; 
    }
};

}

template <typename Iteraotr>
Iteraotr next(Iteraotr iter, size_t n){
    return impl::Helper<typename std::iterator_traits<Iteraotr>::iterator_category>::next(iter, n);
}


int main(){
    std::vector<double> vec = {5.7, 6.7, 7.7, 2.7};
    std::list lst{1.2, 2.3, 4.5, 6.7, 7.8};

    // can use gdb to find the difference or add print or log.
    std::cout << *next(vec.begin(), 2) << std::endl;
    std::cout << *next(lst.begin(), 2) << std::endl;
}
