#include <iostream>
#include <functional>
#include <boost/type_index.hpp>
#include <boost/core/demangle.hpp>

using boost::core::demangle;
using namespace boost::typeindex;
using namespace std::placeholders;

class RefType{
public:
    double& serialize() {};
};

struct func_{
    template<typename T>
    decltype(auto) operator()(T& t){
        return t.serialize(); 
    } 

    template<typename T>
    decltype(auto) operator()(T& t) const {
        return t.serialize(); 
    } 

    /* const can lead to overload, but noexcept can't. */
    //template<typename T>
    //decltype(auto) operator()(T& t) noexcept {
    //    return t.serialize(); 
    //} 

    template<typename T>
    auto operator()(T &t) const -> decltype(t.serialize()) { // using explicit decltype() is nice for a SFINAE!
        return t.serialize();
    }
};

void test(){
    RefType tmp;
    
    auto func = [](auto& t) -> decltype(auto) {
        return t.serialize(); 
    };
    
    //auto func = [](const auto& t) -> decltype(auto) {
    //    return t.serialize(); 
    //};
    
    std::cout << "lambda decltype(auto): " << demangle(typeid(func(tmp)).name()) << std::endl;
    std::cout << "lambda decltype(auto): " << type_id_with_cvr<decltype(func(tmp))>() << std::endl;
    std::cout << "functor decltype(auto): " << demangle(typeid(func_{}(tmp)).name()) << std::endl;
    std::cout << "functor decltype(auto): " << type_id_with_cvr<decltype(func_{}(tmp))>()<< std::endl;

    constexpr auto fixed_val = 7.7;
    auto add = std::bind(std::plus<double>(), _1, fixed_val);
    auto add_ = [fixed_val](double para){ return para + fixed_val; };
    auto add__ = [](const double fix_val){
        return [fix_val](double para){ return para + fixed_val; };
    };
}

int main(){
    test();
    return 0;
}
