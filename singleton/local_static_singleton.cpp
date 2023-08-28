#include <iostream>
#include <pthread.h>
#include "local_static_singleton.h"


singleton* singleton::ptr;

singleton* singleton::instance(){
    static singleton s_var;
    return &s_var;
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
