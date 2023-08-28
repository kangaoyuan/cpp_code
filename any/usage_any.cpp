#include <any>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <boost/type_index.hpp>
#include <boost/core/demangle.hpp>

using std::vector;
using boost::core::demangle;
using namespace boost::typeindex;
using namespace std::string_literals;

void test1(){
    std::any a;         // default constructor
    std::any b{3};      // direct constructor using uniform initializer
    std::any c = std::make_any<double>(2.7);
    // Initialize std::any object, which must be copy constructible
    auto d = std::make_unique<double>(7.7);
    /* copy constructor, if in operator= leftside and rightside are different
     * types, compiler will lead to type cast */
    //std::any d = std::make_unique<double>(7.7); // error
}

void test2(){
    /* The value stored in std::any object can be changed by whatever the type object including std::any and other types, but which must be copy constructible. */
    std::any x;         // defualt constructor
    std::cout << std::boolalpha << "x.has_value(): " << x.has_value() << std::endl;
    x = "hello world!";
    std::any y(42);     // direct constructor
    y = x;
    y.reset();
    // std::cout << type_id<decltype(x)>() << std::endl;
    std::cout << demangle(typeid(x).name()) << std::endl;
    std::cout << demangle(x.type().name()) << std::endl;
    try{
        std::cout << std::any_cast<double>(x) << std::endl; 
    }
    catch(std::bad_any_cast& exception){
        std::cout << "exception:" << exception.what() << std::endl; 
    }
}

void test3(){
    std::any z{27};
    std::cout << "z = " << std::any_cast<int>(z) << std::endl;
    int t = std::any_cast<int>(z);
    //int& a = std::any_cast<int>(z);
    int* p = std::any_cast<int>(&z);
    int& i = *std::any_cast<int>(&z);
    std::cout << "p = " << p << ", &i = " << &i << std::endl;
    ++i;
    std::cout << "i = " << std::any_cast<int>(i) << std::endl;
    std::cout << "z = " << std::any_cast<int>(z) << std::endl;
    
    std::any var1(std::vector{1.2, 3.4, 5.6, 7.8});
    std::cout << demangle(var1.type().name()) << std::endl;
    std::cout << "before .emplace() call: " << std::endl;
    for(const auto& elem : std::any_cast<std::vector<double>>(var1)){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;
    //var1.emplace<std::vector<std::string>>({"jjj", "kkk"} /* no args */);
    var1.emplace<std::vector<std::string>>({"jjj"s, "kkk"s} /* no args */);
    std::cout << "after .emplace() call: " << std::endl;
    for(const auto& elem : std::any_cast<std::vector<std::string>>(var1)){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;
}

int main(){
    test1();
    test2();
    test3();
    return 0;
}
