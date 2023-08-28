#include <map>
#include <iostream>
#include <boost/type_index.hpp>

using namespace boost::typeindex;

// raw array deduction is the important difference between auto and template<typename T> 
template<typename T, auto Size>
void test(T (&array)[Size]){
    std::cout << "Size = " << Size << std::endl;
    std::cout << "one dimension array element type is " << type_id<T>() << std::endl;
}

template<typename K, typename V>
void example(const std::map<K, V>& record){
    std::cout << "The type of map is " << type_id<std::map<K, V>>() << std::endl;
    std::cout << "The type of map is " << type_id<decltype(record)>() << std::endl;
    std::cout << "The key type of map is " << type_id<K>() << std::endl;
    std::cout << "The value type of map is " << type_id<V>() << std::endl;

    // We can find enum class object how to sort by default.
    for(auto&& [key, value] : record){
        std::cout << static_cast<int>(key) << " : " << value <<  std::endl; 
    }
}

enum class enum_case{
    case1 = 2,
    case2 = 5,
    case3 = 9,
    case4 = 7,
};

int main(){
    double arr[7];
    test(arr);

    std::map<enum_case, std::string> record = {{enum_case::case3, "last"}, {enum_case::case1, "begin"}, {enum_case::case2, "missing"}};
    example(record);

    return 0;
}
