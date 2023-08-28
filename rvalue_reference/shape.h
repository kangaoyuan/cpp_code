#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <iostream>
#include <stdexcept>

enum class shape_type {
    circle,
    triangle,
};

class shape {
public:
    //virtual ~shape() = 0;
    virtual ~shape() = default;
};

class circle : public shape {
public:
    circle() { puts("circle()"); }
    ~circle() override { puts("~circle()"); }
};

class triangle : public shape {
public:
    triangle() { puts("triangle()"); }
    ~triangle() override { puts("~triangle()"); }
};

class result {
public:
    result() { puts("result()"); }
    ~result() { puts("~result()"); }
};

shape* create_shape(shape_type type){
    switch (type) {
        case shape_type::circle:
            return new circle;
            // break;       
        case shape_type::triangle:
            return new triangle;
            // break;       // can ignore, here to show the usage of case
    }
    throw std::logic_error("shape type is invalid");
}

#endif
