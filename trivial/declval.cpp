#include <iostream>
#include <boost/type_index.hpp>

using namespace boost::typeindex;

struct MyDefault {
    static int foo()  {
        return 1; 
    }
};

struct NoneDefault {
    // When class defines custom constructor, the default constructor will
    // no longer automatically generate.
    NoneDefault(const NoneDefault& other)= default;
    [[nodiscard]] 
    int foo() const{
        return 1; 
    }
};

int main(){
    std::cout << type_id_with_cvr<decltype(MyDefault{}.foo())>() << std::endl;
    /* compile error */
    //std::cout << type_id_with_cvr<decltype(NoneDefault{}.foo())>() << std::endl;
    /* Avoiding above error, although the class have no constructor, declval<>{} still wroks */
    std::cout << type_id_with_cvr<decltype(std::declval<NoneDefault>().foo())>() << std::endl;
    
}
