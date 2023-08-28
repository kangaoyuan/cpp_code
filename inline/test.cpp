#include "counter.h"

void test() {
    std::cout << "test: value = " << g_counter << " , ptr = " << &g_counter << std::endl;
    dump();
    std::cout << "test: value = " << g_counter << " , ptr = " << &g_counter << std::endl;
}
