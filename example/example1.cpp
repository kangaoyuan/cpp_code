#include <iostream>

struct Env{
    int (*api_1)(int);
    const char* (*api_2)(int, int);
    const char* (*api_3)(int, const char*, const char*);
};

// Here, static is specifier to modify the attribute of function scope.
static int api1_impl(int a){
    return a + 3;
}

static const char* api2_impl(int a, int b){
    return ((a + b) % 2 == 0) ? "sum-even" : "sum-odd";     
}

static const char* api3_impl(int a, const char *b, const char *c){
    return (a % 2 == 0) ? b : c;
}

const Env* get_API(){
    // Here, static is to extend the lifetime of the local variable.
    static const Env env = {
        &api1_impl,
        &api2_impl,
        &api3_impl, 
    };
    return &env;
}

constexpr Env get_API_(){
    // Here, static is to extend the lifetime of the local variable.
    constexpr Env env = {
        &api1_impl,
        &api2_impl,
        &api3_impl, 
    };
    return env;
}

int main() {
    const Env *env = get_API();

    std::cout << env->api_1(5) << std::endl;
    std::cout << env->api_2(1, 2) << std::endl;
    std::cout << env->api_3(5, "even", "odd") << std::endl;

    constexpr Env env_ = get_API_();
    std::cout << env_.api_1(5) << std::endl;
    std::cout << env_.api_2(1, 2) << std::endl;
    std::cout << env_.api_3(5, "even", "odd") << std::endl;

    return 0;
}
