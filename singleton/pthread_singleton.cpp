#include <iostream>
#include <pthread.h>
#include <spdlog/spdlog.h>
#include "pthread_singleton.h"


singleton* singleton::ptr;
pthread_once_t singleton::once = PTHREAD_ONCE_INIT;

// init() is static member function, so no need to pass this pointer.
void singleton::init(){
    ptr = new singleton(); 
    spdlog::info("This function should only be printed once");
}

singleton* singleton::instance(){
    if(ptr == nullptr) {
        pthread_once(&once, &singleton::init); 
    }
    return ptr;
}

void singleton::destroy(){
    delete ptr;
    ptr = nullptr;
}

singleton::singleton(){
    std::cout << "singleton is created" << std::endl;
}

singleton::~singleton(){
    std::cout << "singleton is destroyed" << std::endl;
}

void singleton::do_something(){
    std::cout << "call singleton::do_something" << std::endl;
}
