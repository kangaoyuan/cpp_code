#include <iostream>

class Obj{
public:
    Obj(){
        std::cout << "Obj() constructor" << std::endl; 
    }
    ~Obj(){
        std::cout << "~Obj() destructor" << std::endl;
    }
};

void foo(int n){
    Obj obj;
    if(n == 42){
        throw "throw exception, still triggering destructor";
    }
    std::cout << "This output is in void foo(int) function, but only executing if no exception throw." << std::endl;
}

int main(){
    // When the exception is catched, the destructor is firstly executed and then the catch block will be executed.
    try{
        foo(41); 
        foo(42);
    } catch(const char* str){
        std::cout << str << std::endl; 
    }
    std::cout << "If exception has been catched, the program still running" << std::endl;

    // Attention! if not using try/catch block, the stack unwinding for destructor will not trigger.
    foo(41);
    foo(42);

    std::cout << "If exception has been catched, the program still running" << std::endl;
}
