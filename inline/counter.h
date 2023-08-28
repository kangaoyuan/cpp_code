#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <iostream>

// All inline variables and functions in run-time are mapped into one thing.
// inline int g_counter = 0;
static int g_counter = 0;

inline void dump(){
    std::cout << "dump: value = " << g_counter << " , ptr = " << &g_counter << std::endl;
    ++g_counter;
}

#endif
