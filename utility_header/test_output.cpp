#include <map>
#include <set>
#include <vector>
#include <iostream>
#include "output.h"

using namespace std::string_literals;

int main() {
    std::cout << std::boolalpha;
    std::cout << has_output_v<long long> << std::endl;
    std::cout << has_output_v<std::vector<long long>> << std::endl;
    
    std::map<int, int> mp{{1, 1}, {2, 4}, {3, 9}};
    std::cout << mp << std::endl;
    std::vector<std::vector<int>> vv{{1, 1}, {2, 4}, {3, 9}};
    std::cout << vv << std::endl;

    std::pair<int, int> p{1, 2};
    std::cout << p << std::endl;

    std::set<int> s{1, 2, 3};
    std::cout << s << std::endl;

    std::vector<char> v{'a', 'b'};
    std::cout << v << std::endl;
    // Avoid warning, but can show some circumstances.
    //std::set<char *> vs{"a", "b"};
    std::set<const char *> vs{"a", "b"};
    std::cout << vs << std::endl;

    std::map<int, const char *> mm{{1, "23"}, {2, "234hi"}};
    std::map<int, std::string> mm1{{1, "45"s}, {2, "456hi"s}};
    std::cout << mm << std::endl;
    std::cout << mm1 << std::endl;
}
