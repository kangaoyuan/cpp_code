#include <future>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

// slower routine
int sub_task1(int x){
    std::this_thread::sleep_for(1000ms);
    return x;
}

// faster routine
int sub_task2(int x){
    std::this_thread::sleep_for(500ms);
    return x;
}

int run(int a, int b){
    /* In fundamental, std::async will generate std::thread obj to call .detach() method. Maybe it's the reason why thread and async parameter is passing by value. */
    std::future<int> result1 = std::async(std::launch::async, sub_task1, a);

    int result2 = sub_task2(b);
    if(result2 < 0){
        // Here no resource leak.
        return -2; 
    }

    // std::future<Type> obj calling .get() will block if the thread is not return.
    if(result1.get() < 0){
        // Also no resource leak.
        return -1; 
    }

    return 0;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " [int] [int]" << std::endl;
    return 1;
  }

  std::cout << run(std::stoi(argv[1]), std::stoi(argv[2])) << std::endl;
  return 0;
}
