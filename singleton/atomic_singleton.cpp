#include <atomic>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <spdlog/spdlog.h>
#include "atomic_singleton.h"

std::mutex singleton::lock_;
std::atomic<singleton*> singleton::ptr_;

singleton* singleton::instance(){
    singleton* ptr = ptr_.load(std::memory_order_acquire);
    if(ptr == nullptr){
        std::lock_guard guard{lock_};
        ptr = ptr_.load(std::memory_order_acquire);
        if(ptr == nullptr){
            ptr = new singleton();
            ptr_.store(ptr, std::memory_order_release);
            spdlog::info("This function should only be printed once");
        }
    }
    return ptr;
}

void singleton::destroy(){
    std::lock_guard guard{lock_};
    singleton* ptr = ptr_.load(std::memory_order_acquire);
    if(ptr != nullptr){
        delete ptr_;
        ptr_.store(nullptr, std::memory_order_release);
    }
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
