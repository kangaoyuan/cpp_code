#include <list>
#include <vector>           
#include <iostream>         // std::cout...
#include <type_traits>      // std::decay_t<>

template<template<typename, typename> class OutputContainer = std::vector,
         typename Func, typename ResourceContainer>
decltype(auto) fmap(Func&& func, ResourceContainer&& input){
    using result_type = std::decay_t<decltype(func(*input.begin()))>;
    // using result_type = std::decay_t<std::result_of_t<Func(decltype(*input.begin()))>>;
    OutputContainer<result_type, std::allocator<result_type>> result;

    for(auto&& elem : input){
        result.push_back(func(std::forward<decltype(elem)>(elem)));  
    }

    return result;
}

int main(){
    std::vector vec{1.2, 2.3, 4.5, 6.7};

    std::cout << "the content of resource inputs:" << std::endl;
    for(const auto& elem: vec){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;

    auto result = fmap([](decltype(*vec.begin()) resource_elem){
        return resource_elem * 2 + 1;                            
    }, vec);

    std::cout << "the result of map multiplying 2 and adding 1:" << std::endl;
    for(const auto& elem: result){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;

    auto others = fmap<std::list>([](decltype(*vec.begin()) resource_elem){
        return (resource_elem + 1) * 2;                            
    }, vec);

    std::cout << "the result of map multiplying 2 and adding 1:" << std::endl;
    for(const auto& elem: others){
        std::cout << elem << " "; 
    }
    std::cout << std::endl;

    return 0;
}
