#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>

class scoped_thread_join {
public:
    /* thread obj can't be copied, must pass by reference. */
    explicit scoped_thread_join(std::thread& thread) : m_thread(thread) {}
    //explicit scoped_thread_join(std::thread& thread) : thread_(thread) {}
    //explicit scoped_thread_join(std::thread&& thread) : m_thread(thread) {}

    //template<typename... Args>
    //scoped_thread_join(Args&&... args): m_thread(std::thread{std::forward<Args>(args)...}){}

    ~scoped_thread_join() {
        /* Allowing call .join() early before destructor. */
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }

private:
    //std::thread m_thread;
    //std::thread* m_thread;
    std::thread& m_thread;
};

std::atomic_bool is_ready = false;
std::mutex cv_mtx;
std::condition_variable cv;

bool is_valid(int x) {
    return x % 2 == 0;
}

int subtask1(int x) {
    std::unique_lock<std::mutex> lck(cv_mtx);
    cv.wait(lck, []() { return is_ready == true; });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return x;
}

int subtask2(int x) {
    if (!is_valid(x)) {
        return -1;  // Problemetic, subtask1 always don't get notification.
    }

    // Here sleep to guarantee .notify_one() or .notify_all() behind .wait()
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    //atomic variable modification don't need mutex
    //std::lock_guard<std::mutex> lock(mtx);
    is_ready = true;
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    return x;
}

int run(int a, int b) {
    int result1;
    std::thread t([&]() { result1 = subtask1(a); });
    // RAII to manage the thread resource
    scoped_thread_join thread_guard(t);

    int result2 = subtask2(b);
    if (result2 < 0) {
        return -2;
    }

    // In destructor to judge whether joinable, so can early call .join() and guarantee the capture variables by reference is not out of lifetime.
    t.join();
    if (result1 < 0) {
        return -1;
    }

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
