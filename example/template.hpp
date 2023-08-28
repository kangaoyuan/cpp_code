#include <iostream>
#include <ostream>
#include <utility>

void dump_values(std::ostream &os) {}

//template <typename A0>
//void dump_values(std::ostream &os, A0 &&a0) {
//  os << a0;
//}
//
//template <typename A0, typename A1, typename... Args>
//void dump_values(std::ostream &os, A0 &&a0, A1 &&a1, Args &&...args) {
//  os << a0 << ", ";
//  dump_values(os, std::forward<A1 &&>(a1), std::forward<Args &&>(args)...);
//}

template <typename Type, typename... Args>
void dump_values(std::ostream& os, Type arg, Args&&... args){
    os << arg;
    ((os << ", " << args), ...) ;
}

template <typename... Args>
void dump_call(std::ostream &os, const char *name, Args&&...args) {
    os << "[trace] " << name << "(";
    dump_values(os, std::forward<Args>(args)...);
    os << ")" << std::flush;
}

template <auto Func, const char *Name> struct LoggerImpl;

template <typename ReturnType, typename... Args,
          ReturnType (*Func)(Args...),
          const char *Name>
struct LoggerImpl<Func, Name> {
    /* Following part code is error, because T&& as universal reference only 
     * when T is function template parameter, not class template paramerter */
    //static ReturnType call(Args&&... args) {
    static ReturnType call(Args... args) {
        // The next two statement std::forward can be ingored.
        auto result = Func(std::forward<Args>(args)...);
        dump_call(std::cerr, Name, std::forward<Args>(args)...);
        std::cerr << " -> " << result << std::endl;
        return result;
    }
};

template <auto Func, const char* Name>
constexpr auto Logger = LoggerImpl<Func, Name>::call;
