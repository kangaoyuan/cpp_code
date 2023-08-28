#include "counter.h"

// the extern keyword modifying the function can be ignored.
extern void test();

int main(){
    std::cout << "main: value = " << g_counter << " , ptr = " << &g_counter << std::endl;
    dump();
    std::cout << "main: value = " << g_counter << " , ptr = " << &g_counter << std::endl;
    test();
    std::cout << "main: value = " << g_counter << " , ptr = " << &g_counter << std::endl;

    return 0;
}
