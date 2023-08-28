#include <future>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

// slower routine
int sub_task1(int x){
    std::this_thread::sleep_for(700ms);
    return x;
}

// faster routine
int sub_task2(int x){
    std::this_thread::sleep_for(300ms);
    return x;
}

int run(int a, int b){
    //std::future<int> future1 = async(std::launch::async, sub_task1, a);
    int result1;
    std::thread t([&]() { result1 = sub_task1(a); });

    int result2 = sub_task2(b);

    if(result2 < 0){
        // Attention! Attention!!!, This is serious, why we need RAII obj to guard the resources, such as pointer, mutex, thread.
        return -2; 
    }

    //int result1 = future1.get();
    t.join();
    return result1 < 0 ? -1 : 0;
    //if(result1 < 0){
    //    return -1; 
    //}

    //return 0;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " [int] [int]" << std::endl;
    return 1;
  }

  std::cout << run(std::stoi(argv[1]), std::stoi(argv[2])) << std::endl;
  return 0;
}
