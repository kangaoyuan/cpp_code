#pragma once

#include <pthread.h>

class singleton{
public:
    singleton(const singleton&) = delete;
    singleton& operator = (const singleton&) = delete;
    static singleton* instance();
    static void destroy();
    void do_something();
private:
    // Here singleton() and ~singleton() can't be declared as = delete;
    singleton();
    ~singleton();
    static void init();
    static singleton* ptr;
    static pthread_once_t once;
};
