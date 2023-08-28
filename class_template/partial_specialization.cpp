#include <iterator>
#include <iostream>
#include <algorithm>

template<auto Ptr>
struct GetterImpl{};

// Non-type template parameter partial specialization, specializing Ptr.
template<typename DataType, typename ClassType,
         DataType ClassType::*Ptr>
struct GetterImpl<Ptr> {
/* The below definition is wrong, because the Ptr type is unknown */
//template<typename DataType, typename ClassType>
//struct GetterImpl<DataType ClassType::*Ptr> {
    static const DataType& getter(const ClassType& obj){
        return obj.*Ptr; 
    }
};

template<auto Ptr>
auto Getter = GetterImpl<Ptr>::getter;

struct X {
  int a;
  double b;
};

int main() {
  X xs[] = { {1, 2.3}, {4, 5.6}, {7, 8.9} };

  std::cout << "int:" << std::endl;
  std::transform(std::begin(xs), std::end(xs),
                 std::ostream_iterator<int>(std::cout, " "),
                 Getter<&X::a>);  
  std::cout << std::endl;

  std::cout << "double:" << std::endl;
  std::transform(std::begin(xs), std::end(xs),
                 std::ostream_iterator<double>(std::cout, " "),
                 Getter<&X::b>); 
  std::cout << std::endl;

  return 0;
}
