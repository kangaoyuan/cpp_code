#include <array>
#include <iostream>

constexpr int const_size = 5;

class Rect{
public:
    constexpr Rect()= default;
    constexpr Rect(double height, double width): m_hegiht(height), m_width(width){}
    /* constexpr const class member functions can be evaluated at compile-time. */
    [[nodiscard]] 
    constexpr double get_area() const {
        return m_hegiht * m_width; 
    }
private:
    double m_hegiht = {};
    double m_width = {};
};

int main(){
    static_assert(const_size > 0, "constexpr varibale can be executed at compile time");
    // constexpr function can be executed at run time. However, it need at least one circumstance to be executed at compile time.
    static_assert(Rect{3, 5}.get_area() == 15, "constexpr function can be applied as constructor");

    std::cout << "Input two value as rectangle hegiht and width:" << std::endl;
    double height, width; 
    if(std::cin >> height && std::cin >> width){
        std::cout << "Rectangle's area == " << Rect(height, width).get_area() << std::endl;
    }
}
