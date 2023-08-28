#ifndef __SMART_PTR_H__
#define __SMART_PTR_H__

#include <atomic>
#include <algorithm>
#include <stdexcept>

class shared_count{
public:
    shared_count() = default;

    operator bool(){
        return m_count != 0; 
    }
    
    long operator++(){
        return ++m_count; 
    }

    long operator--(){
        return --m_count; 
    }

    void add_count() {
        ++m_count; 
    }

    void reduce_count() {
        --m_count; 
    }

    [[nodiscard]]
    long get_count() const {
        return m_count; 
    }
private:
    std::atomic_long m_count = {1};
};

template<typename T>
class shared_ptr{
template <typename U>
friend class shared_ptr;
public:
    explicit shared_ptr(T* ptr = nullptr): m_ptr(ptr), m_counter(new shared_count{}){}
    //{
    //    if(m_ptr) {
    //        m_counter = new shared_count{}; 
    //    }
    //}
    
    shared_ptr(const shared_ptr& other) {
        m_ptr = other.m_ptr;
        m_counter = other.m_counter;
        //m_counter->add_count(); 
        /* Equal statement, Although other is const, but it only limits itslef
         * data member. We still can use poniter to modify. */
        other.m_counter->add_count();
    }

    // This is not copy ctor, the system still generate the defualt one, which is wrong. So we provides the above one overwrite the copy ctor.
    template<typename U>
    shared_ptr(const shared_ptr<U>& other) {
        m_ptr = other.m_ptr;
        m_counter = other.m_counter;
        //m_counter->add_count(); 
        /* Equal statement, Although other is const, but it only limits itslef
         * data member. We still can use poniter to modify. */
        other.m_counter->add_count();
    }

    template<typename U>
    shared_ptr(shared_ptr<U>&& other) noexcept {
        m_ptr = other.m_ptr;
        // Attention the sequence!!!
        m_counter = other.m_counter;
        other.m_ptr = nullptr;
    }

    shared_ptr& operator=(shared_ptr rhs) noexcept {
        swap(rhs);
        return *this;
    }

    T& operator*() const {
        if(m_ptr){
            return *m_ptr; 
        }              
        throw std::logic_error("dereference nullptr");  
    }

    T* operator->() const {
        if(m_ptr){
            return m_ptr; 
        }              
        throw std::logic_error("dereference nullptr");  
    }

    operator bool() const {
        return m_ptr != nullptr;  
    }

    T* get() const {
        return m_ptr; 
    }

    [[ nodiscard ]]
    long get_count() const {
        //return m_counter->get_count(); 
        return m_ptr ? m_counter->get_count() : 0;
    }

    void reset(T* ptr) {
        ~shared_ptr(); 
        m_ptr = ptr;
        m_counter = new shared_count{};
    }

    void swap(shared_ptr& other){
        using std::swap;
        swap(m_ptr, other.m_ptr);
        swap(m_counter, other.m_counter);
    }

    ~shared_ptr() noexcept {
        --*m_counter; 
        //m_counter->reduce_count();
        if(!*m_counter){
        //if(!m_counter->get_count()){
            delete m_ptr;
            delete m_counter; 
        }
    }
private:
    T* m_ptr;   // = nullptr;
    shared_count* m_counter = nullptr;
};


template<typename T>
void swap(shared_ptr<T>&lhs, shared_ptr<T>&rhs) noexcept {
    lhs.swap(rhs);
}

#endif
