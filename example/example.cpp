#include <iostream>
#include "template.hpp"

struct Env {
    int (*api1)(int);
    const char *(*api2)(int, int);
    const char *(*api3)(int, const char *, const char *);
};

static int api1(int a) {
    return a + 1;
}

static const char *api2(int a, int b) {
    return ((a + b) % 2 == 0) ? "sum-even" : "sum-odd";
}

static const char *api3(int a, const char *b, const char *c) {
    return (a % 2 == 0) ? b : c;
}

static int api1_debug(int a) {
    std::cerr << "[trace] api1(" << a << ")" << std::flush;
    auto result = api1(a);
    std::cerr << " -> " << result << std::endl;
    return result;
}

static const char *api2_debug(int a, int b) {
    std::cerr << "[trace] api2(" << a << ", " << b << ")" << std::flush;
    auto result = api2(a, b);
    std::cerr << " -> " << result << std::endl;
    return result;
}

static const char *api3_debug(int a, const char *b, const char *c) {
    std::cerr << "[trace] api3(" << a << ", " << b << ", " << c << ")"
        << std::flush;
    auto result = api3(a, b, c);
    std::cerr << " -> " << result << std::endl;
    return result;
}

const Env *GetAPI() {
    const bool is_debug_mode = std::getenv("DEBUG") != nullptr;

    static const Env env = {
        &api1,
        &api2,
        &api3,
    };

    static constexpr char api1_name[] = "api1";
    static constexpr char api2_name[] = "api2";
    static constexpr char api3_name[] = "api3";

    static const Env env_debug = {
        Logger<&api1, api1_name>,
        Logger<&api2, api2_name>,
        Logger<&api3, api3_name>,
    };

    return is_debug_mode ? &env_debug : &env;
}

const Env* _GetAPI() {
    const bool is_debug_mode = std::getenv("DEBUG") != nullptr;
#define  FOR_EACH_API(V) \
    V(api1) \
    V(api2) \
    V(api3) \

    static const Env env = {
#define DEFINE_API(X) &X,
        FOR_EACH_API(DEFINE_API) 
#undef DEFINE_API
    };

#define DEFINE_API_NAME(X) static constexpr char X##_name[] = #X;
    FOR_EACH_API(DEFINE_API_NAME)
#undef DEFINE_API_NAME

    static const Env env_debug = {
#define DEFINE_API(X) Logger<&X, X##_name>,
        FOR_EACH_API(DEFINE_API) 
#undef DEFINE_API
    };
#undef FOR_EACH_API
    return is_debug_mode ? &env_debug : &env;
}

int main() {
    const Env *env = _GetAPI();

    std::cout << env->api1(5) << std::endl;
    std::cout << env->api2(1, 2) << std::endl;
    std::cout << env->api3(5, "even", "odd") << std::endl;

    return 0;
}
