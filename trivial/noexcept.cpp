#include <iostream>

class Base{
public:
    virtual void foo() noexcept {}
};

class Derived final: public Base{
public:
    /* Error! noexcept will influence function override */
    //void foo() override {}
};

void example_oveload(int p) {
    std::cout << "may throw function" << std::endl;    
}
/* Error! return type is not the signature, which can't lead to fuction
 * overloading */
//double exampel_oveload(int p) {}

/* Error! noexcept is not the signature, which also can't lead to function
 * overloading*/
//void example_oveload(int p) noexcept {
//    std::cout << "noexcept function" << std::endl;    
//}

void example_may_throw(){}
void example_no_throw() noexcept {}

// Two test are function overloading, beacause the ptr are two different types.
void test(void (*ptr)()){
    std::cout << "ptr may throw: " << reinterpret_cast<void *>(ptr) << std::endl;
}

// Only accept the noexcept specifier modified function
void test(void (*ptr)() noexcept){
    std::cout << "ptr doesn't throw: " << reinterpret_cast<void *>(ptr) << std::endl;
}

class A{
public:
    A() = default;
    A(const A& other) = default;

    // member functions can't lead to ADL
    void swap(A& rhs) noexcept {}
};

void swap(A& lhs, A& rhs) noexcept {

}

class B{
public:
    // Optimized version
    void apply(void (*transform)(A&) noexcept){
        transform(m_a0); 
        transform(m_a1); 
    }

    // Safe version (Perfomance loss)
    void apply(void (*transform)(A&)){
        A a0_tmp(m_a0); 
        transform(a0_tmp);

        A a1_tmp(m_a1);
        transform(a1_tmp);

        // Attention! ADL applies to functions and not to member functions. 
        swap(m_a0, a0_tmp);
        swap(m_a1, a1_tmp);
    }
private:
    A m_a0;
    A m_a1;
};

int main(){
    test(example_may_throw);
    test(&example_no_throw);

    using func_ptr = void (*)() noexcept;
    func_ptr ptr1 = example_no_throw;
    /* error! assign no noexcept function address to noexcept function pointer*/
    // func_ptr ptr2 = example_may_throw;
}
