#include <ios>
#include <utility>
#include <iostream>

class Waiting{
public:
    double& do_something(long, long long&, int&&){}
};

template<typename Func>
struct Test{
private:
    template<typename... Params>
    constexpr auto test(Func* ptr)
    ->decltype(std::declval<Func>()(std::declval<Params>()...), true) {
        return true; 
    }
    
    template<typename... Params>
    constexpr auto test(...){
        return false; 
    }

public:
    template<typename... Params>
    auto operator()(Params&&... params){
        return test<Params...>(nullptr); 
    }

    template<typename... Params>
    constexpr auto test_(Params&&... params)
    ->decltype(std::declval<Func>()(std::declval<Params>()...), true) {
        return true; 
    }

    
    constexpr auto test_(...) {
        return false; 
    }

    // ctor for class template argument deduction
    Test(Func func){};
};

int main(){
    Waiting obj;
    long long var = 77LL;
    auto func = [&obj](long p1, long long& p2, int p3){ obj.do_something(p1, p2, std::move(p3)); };

    std::cout << std::boolalpha;
    std::cout << Test{func}.test_(44, 55) << std::endl;
    std::cout << Test{func}.test_(44, 11, 55) << std::endl;
    std::cout << Test{func}.test_(44, var, 55) << std::endl;
    return 0;
}
