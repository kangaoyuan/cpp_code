#include <vector>
#include <thread>
#include "pthread_singleton.h"

void do_something(){
    singleton::instance()->do_something();
}


int main(){
    std::vector<std::thread> threads;
    for(int i = 0; i < 7; i++){
        threads.emplace_back(do_something); 
    }

    for(auto&& thrd : threads) {
        thrd.join(); 
    }

    singleton::destroy();

    return 0;
}
