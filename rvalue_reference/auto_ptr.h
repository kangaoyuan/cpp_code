#ifndef __SMART_PTR_H__
#define __SMART_PTR_H__

#include <algorithm>

template<typename T>
class auto_ptr{
public:
    explicit auto_ptr(T* ptr = nullptr): m_ptr(ptr) {}

    /* when other is const lvalue can't call non-const member functions */
    //auto_ptr(const auto_ptr& other) {
    /* here implementing unique semantic, no copy constructor only move */
    //auto_ptr(auto_ptr&& other) {
    auto_ptr(auto_ptr& other) {
        m_ptr = other.release(); 
    }

    auto_ptr& operator=(auto_ptr rhs) {
        swap(rhs); 
        // Equal statement
        // rhs.swap(*this);
        return *this;
    }
    
    T& operator*() const {
        return *m_ptr; 
    }

    T* operator->() const {
        return m_ptr; 
    }

    operator bool() const {
        return m_ptr != nullptr; 
    }

    T* get() const {
        return m_ptr; 
    }

    T* release() {
        T* ptr = m_ptr; 
        m_ptr = nullptr;
        return ptr;
    }

    void reset(T* ptr = nullptr) {
        delete m_ptr;
        m_ptr = ptr; 
    }

    void swap(auto_ptr& rhs){
        using std::swap;
        swap(m_ptr, rhs.m_ptr);
    }

    ~auto_ptr() {
        delete m_ptr; 
    }
private:
    T* m_ptr;
};

template<typename T>
void swap(auto_ptr<T>& lhs, auto_ptr<T>& rhs) {
    lhs.swap(rhs); 
}

#endif
