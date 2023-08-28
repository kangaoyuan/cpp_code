#include <ios>
#include <iostream>
#include <type_traits>

struct A{};

struct B: public A {
    std::string serialize() const {
        return "hi"; 
    }
};

struct C {
    struct Func {
        std::string operator()() {
            return "I am C!";
        }
    };

    Func serialize;
};


template<typename T>
struct has_serialize {
;
    template<typename U, std::string (U::*)() const>
    struct SFINAE{};

    template<typename U>
    static constexpr bool test(SFINAE<U, &U::serialize> *ptr) { return true; }

    template<typename U>
    static constexpr bool test(...) { return false; }

    static constexpr bool value = test<T>(nullptr);
};

template<typename T>
bool has_serialize_v = has_serialize<T>::value;

template<typename T>
bool test_has_serialize(const T& p){
    return has_serialize<T>::value;
}

int main(){
    B b;
    // Static type, dynamic type.
    A& a = b;
    std::cout << std::boolalpha;
    std::cout << test_has_serialize(a) << std::endl;
    std::cout << test_has_serialize(b) << std::endl;

    C c;
    std::cout << c.serialize() << std::endl; 
    std::cout << has_serialize_v<C> << std::endl; 

    return 0;
}


