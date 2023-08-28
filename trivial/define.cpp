#include <iostream>

#define STR(X) #X
#define XSTR(X) STR(X)

// Object-like Macro
//#define bcopy __bionic_bcopy
/* Function-like Macro */
#define bcopy(src, dst, size) __bionic_copy(src, dst, size)

#define CONFIG 4
const char example1[] = STR(CONFIG);  // "CONFIG"
const char example2[] = XSTR(CONFIG);  // "4"

enum BuiltinFunc{
#define BUILTIN(NAME) BUILTIN_##NAME,
#ifndef BUILTIN_LIBC
    #define BUILTIN_LIBC(NAME) BUILTIN(NAME)
#endif
/* For bcopy as actual argument and it not related with # or ##, it will be replaced. */
/* If bcopy is a Function-like Macor, it must need parenthesis to expand. So it doesn't be repalced */
    BUILTIN_LIBC(bcopy)
};

void HandleBuiltin(BuiltinFunc func){
    //if(func == BUILTIN___bionic_bcopy){
    if(func == BUILTIN_bcopy){
    
    }
}

int main(){
    // 1. In Function-like Macro Invocation, if the formal parameter in macro body related with # or ##, the formal parameter will not be replaced or expanded and directly operate with # or ##.
    std::cout << "#define CONFIG 3" << std::endl;
    std::cout << "#define STR(X) #X" << std::endl;
    std::cout << "STR(CONFIG): " << STR(CONFIG) << std::endl;
    // The formal parameter is not related with # or ## operators. So the preprocessor will firstly replace or expand the actual argument to formal parameter
    std::cout << "#define XSTR(X) STR(X)" << std::endl;
    std::cout << "XSTR(CONFIG): " << XSTR(CONFIG) << std::endl;

    // 2. When Function-like Macro Invocation be expanded, If the content still has Macro and the Macro is not the Macro itself, the preprocessor will still work until no Macro to replace. Next Macro is error for recursion(itself).
#define EXAMPLE(X) (EXAMPLE(X + 1) - EXAMPLE(1))
    // EXAMPLE(5)
}
