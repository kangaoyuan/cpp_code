#include <iostream>

//auto test_(int path){
//    if(path == 0) 
//        return 1.0;
//    else if(path == 1)
//        return 42u;
//}

template <int Case>
auto test() {
  if constexpr (Case == 0) {
    return 1.0;
  } else if constexpr (Case == 1) {
    return 42u;
  } else {
    return "hello world";
  }
}

int main() {
  std::cout << test<0>() << std::endl;
  std::cout << test<1>() << std::endl;
  std::cout << test<2>() << std::endl;
}
