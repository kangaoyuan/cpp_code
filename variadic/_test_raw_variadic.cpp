#include <iostream>
#include <string>
#include <utility>

template <typename... Types>
class Helper {};

template <typename Type0>
class Helper<Type0> {
public:
    static Type0 sum(Type0 x0) {
        return std::forward<Type0>(x0);
    }
};

template <typename Type0, typename Type1>
class Helper<Type0, Type1> {
public:
    static auto sum(Type0 x0, Type1 x1) -> decltype(
                                                        std::forward<Type0>(x0) + std::forward<Type1>(x1)) {
        return std::forward<Type0>(x0) + std::forward<Type1 &&>(x1);
    }
};

template <typename Type0, typename Type1, typename... Types>
class Helper<Type0, Type1, Types...> {
public:
    static auto sum(Type0 x0, Type1 x1, Types... xs)
        -> decltype(Helper<decltype(x0 + x1), Types...>::sum(
                                                             std::forward<Type0>(x0) + std::forward<Type1>(x1),
                                                             std::forward<Types>(xs)...)) {
            return Helper<decltype(x0 + x1), Types...>::sum(
                                                            std::forward<Type0>(x0) + std::forward<Type1>(x1),
                                                            std::forward<Types>(xs)...);
        }
};

    template <typename... Types>
auto sum(Types&&... xs)
    -> decltype(Helper<Types&&...>::sum(std::forward<Types&&>(xs)...)) {
        return Helper<Types&&...>::sum(std::forward<Types&&>(xs)...);
    }

int main() {
    std::cout << sum(1) << std::endl;
    std::cout << sum(1, 2) << std::endl;
    std::cout << sum(1, 2, 3) << std::endl;
    std::cout << sum(1, 2, 3, 4) << std::endl;

    std::cout << sum(std::string("a")) << std::endl;
    std::cout << sum(std::string("a"), "b", "c") << std::endl;

    double var1 = 27.7;
    double var2 = 77.7;
    double var3 = 99.9;
    std::cout << sum(var1, var2, var3) << std::endl;
    std::cout << sum(var1, 3, var3) << std::endl;
}
