#include <algorithm>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>

using namespace std::chrono_literals;

// slower routine
int subtask1(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return x;
}

// faster routine
int subtask2(int x) {
    std::this_thread::sleep_for(500ms);
    return x;
}

int run(int a, int b) {
    int result1;
    std::condition_variable dead_cv;

    /* When the std::thread object is running, if the reference objects captured inside it is out of the lifetime. Although calling .detach, whatever, the thread is always dangerous. */
    std::thread t([&]() { 
        result1 = subtask1(a); 
        std::mutex mtx;
        /* The next statement is only to demonstrate the functionality of unique_lock<> with some flag. */
        mtx.lock();
        std::unique_lock<std::mutex> lck(mtx, std::adopt_lock);
        dead_cv.wait(lck); 
        }
    );


    int result2 = subtask2(b);
    if (result2 < 0) {
        /*one bug is in there, there is why RAII is important. But fixing it still has another problem in some circumstance, such as: dead lock for thread t never get notified. */
        t.join();
        //or t.detach();
        return -2;
    }

    t.join();
    /* This is where causes dead lock. because previous .join() statement is a synchronization mechanism for thread t ending, but thread t waiting notifying will never executed befor t.join, this is dead_lock. */
    dead_cv.notify_one();
    return  result1 < 0 ? -1 : 0;
    //if (result1 < 0) {
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
