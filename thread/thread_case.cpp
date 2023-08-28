#include <mutex>
#include <future>
#include <atomic>
#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>

using namespace std::chrono_literals;

class scoped_thread_join {
public:
    // variadic template argument + universal reference + perfect forward
    template <typename... Args>
    scoped_thread_join(Args&&... args): m_thread(std::forward<Args>(args)...){}

    // rvalue reference itself is lvalue.
    explicit scoped_thread_join(std::thread& thread): m_thread(std::move(thread)){}
    explicit scoped_thread_join(std::thread&& thread): m_thread(std::forward<std::thread>(thread)){}

    ~scoped_thread_join(){
        // call .joinable() is important for scoped_thread_join class in destructor to guarantee the underlying thread object maybe call .join() or .detach() before destructor.
        if(m_thread.joinable()){
            m_thread.join();
        }
    }
private:
    std::thread m_thread;
};

std::mutex mtx;
std::condition_variable cv;
std::atomic_bool is_error = false; // Added
std::atomic_bool is_ready = false;

int sub_task1(int x){
    // std::condition_variable calling .wait() method, always need mutex.
    std::unique_lock<std::mutex> lck(mtx, std::defer_lock);
    lck.lock();
    cv.wait(lck, []() { return is_ready || is_error; });

    std::this_thread::sleep_for(1000ms);
    return is_error ? -1 : x; // Added
}

int sub_task2(int x){
    std::this_thread::sleep_for(200ms);
    if([&](){ return x % 2 == 1; }()){
        is_error = true; 
        cv.notify_all();
        return -1; 
    }

    is_ready = true;
    cv.notify_all();

    std::this_thread::sleep_for(300ms);
    return x;
}

int run(int a, int b){
    //int result1;
    //std::thread t([&]() { result1 = sub_task1(a); });
    std::packaged_task<int()> job([&a](){ return sub_task1(a); });
    std::future<int> result1 = job.get_future();
    // std::packaged_task<> obj can't be copied, only be moved.
    std::thread t(std::move(job));
    scoped_thread_join t_guard{t};

    int result2 = sub_task2(b);

    if(result2 < 0){ return -2; }
    // because std::future<Type> obj calling .get() will block if thread not returned. We don't need call .join(). 
    // t.join();    // and t is be moved, we can't use it again. 
    if(result1.get() < 0){return -1;}

    return 0;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " -1 -3" << std::endl;
    return 1;
  }

  std::cout << run(std::stoi(argv[1]), std::stoi(argv[2])) << std::endl;
  return 0;
}
