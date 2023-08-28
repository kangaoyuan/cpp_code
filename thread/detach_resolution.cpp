#include <mutex>
#include <atomic>
#include <thread>
#include <iostream>
#include <condition_variable>

using namespace std::chrono_literals;

int sub_task1(int x){
    std::this_thread::sleep_for(1000ms);
    return x;
}

int sub_task2(int x){
    std::this_thread::sleep_for(500ms);
    return x;
}

struct Sync{
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic_int result1 = {};
    std::atomic_bool is_ready = false;
};

int run(int a, int b){
    auto sync = std::make_shared<Sync>();

    // Notice: pass by shared_ptr<> will solve the lifetime problem.
    std::thread t1 ([a, &sync](){
        sync->result1 = sub_task1(a); 
        sync->is_ready = true;
        sync->cv.notify_one();
    });
    t1.detach();

    int result2 = sub_task2(b);
    if(result2 < 0) { return -2; }

    // Only .wait() need mutex to lock for std::condition_variable<>
    std::unique_lock<std::mutex> lck(sync->mtx);
    sync->cv.wait(lck, [&sync](){ return sync->is_ready == true; });

    if(sync->result1 < 0) { return  -1;}

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
