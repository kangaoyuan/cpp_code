#include <utility>
#include <iostream>

template<typename... Types>
auto diff_left_assoc(Types&&... ops){
    return (... - std::forward<Types>(ops));
}

template<typename... Types>
auto diff_right_assoc(Types&&... ops){
    return (std::forward<Types>(ops) - ...);
}

int main(){
    std::cout << diff_left_assoc(1, 2, 3, 4, 5) << std::endl;
    std::cout << diff_right_assoc(1, 2, 3, 4, 5) << std::endl;
}
