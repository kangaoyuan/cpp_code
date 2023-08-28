#include <cmath>
#include <future>
#include <cassert>
#include <iostream>

class Example1{
public:
    explicit Example1(double value = 7.7): m_value(value){}

    void test(){
        /* [&],[=] all implicitly capture this poniter(by reference) 
         * this pointer must be captured by =, &, *this, this. */
        // auto func = [](){ ++m_value };   // Not capture this pointer, error.
        auto func1 = [&](){ ++m_value; }; 
        auto func2 = [=](){ ++m_value; }; 

        assert(m_value == 7.7);
        func1();
        std::cout << "after call [&](){ ++m_value };, value = " << m_value << std::endl;
        assert(m_value == 8.7);
        func2();
        std::cout << "after call [=](){ ++m_value };, value = " << m_value << std::endl;
        assert(m_value == 9.7);
    }
private:
    double m_value = {};
};

class Example2{
public:
    explicit Example2(double value = 7.7): m_value(value){}

    void test(){
        auto func1 = [this](){ ++m_value; }; 
        // *this in capture list explicitly passes by value, so wo need to add mutable to modify.
        auto func2 = [*this]() mutable { ++m_value; }; 

        assert(m_value == 7.7);
        func1();
        std::cout << "after call [this](){ ++m_value };, value = " << m_value << std::endl;
        assert(m_value == 8.7);
        func2();
        std::cout << "after call [*this](){ ++m_value };, value = " << m_value << std::endl;
        //assert(m_value == 9.7);
    }
private:
    double m_value;
};

class Example3{
public:
    Example3() = default;
    Example3(double value1, double value2): m_value1(value1), m_value2(value2){};

    //decltype(auto) run(){
    std::future<double> run(){
        auto fut = std::async(std::launch::async, [*this](){
            return std::sqrt(m_value1 * m_value1 + m_value2 * m_value2);
        }); 
        /* std::future<> is non-copyable class */
        //auto fut_ = fut;          // error
        /* However, here we don't neeed std::move(). because compiler can help us to utilize rvalue optimization */
        //return std::move(fut);    // ok
        return fut;
    }

private:
    double m_value1 = {};
    double m_value2 = {};
};

int main(){
    Example1 x;
    x.test();

    Example2 y;
    y.test();

    Example3 z(5.0, 12.0);
    std::cout << z.run().get() << std::endl;
    return 0;
}
