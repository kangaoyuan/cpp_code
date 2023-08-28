#include <iostream>

template<typename T>
//void f(const T& t){
void f(const T& t, long long p = 27){
    std::cout << "This is in void f(const T&); function" << std::endl;
}

void f(...){
    std::cout << "This is in void f(...); function" << std::endl;
}

template<typename T>
void _f(const T& t, typename T::iterator p = 27){
    std::cout << "This is in void f(const T&); function" << std::endl;
}

void _f(...){
    std::cout << "This is in void f(...); function" << std::endl;
}

// This is different from _f function template, In function template body, compiler doesn't check and triggers SFINAE. 
template <typename T> 
void func(T t) { 
    t.hahahaICrash(); 
}

//template <typename T> 
void func(...) {
    // The sink-hole wasn't even considered.
    std::cout << "This is in void func(...); function" << std::endl;
} 

struct Type{
    void hahahaICrash(){
        std::cout << "Alough this Type is declared after function template calling. Maybe it will be executed at run-time after compiling" << std::endl; 
    }
};

int main(){
    // function template is more precise than varidaic. 
    f(77.27);

    // When matching function from set to resolute, SFINAE
    _f(27.77);

    // compiler error
    //func("done");
     
    Type tmp;
    func(tmp);

    return 0;
}
