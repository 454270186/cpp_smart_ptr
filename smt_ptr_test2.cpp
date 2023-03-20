#include <iostream>
#include <memory>
#include "smart_ptr.hpp"

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructed." << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructed." << std::endl;
    }

    void do_something() {
        std::cout << "MyClass doing something." << std::endl;
    }
};

int main() {
    // Test make_smart
    smart_ptr<MyClass> ptr = make_smart<MyClass>();
    ptr->do_something();

    smart_ptr<MyClass> ptr2 = ptr;
    std::cout << "Use count of ptr2 is " << ptr2.use_count() << std::endl;
    // Test reset
    ptr.reset();
    if (ptr.get() == nullptr) {
        std::cout << "smart_ptr is null after reset." << std::endl;
    } else {
        std::cout << "smart_ptr is not null after reset." << std::endl;
    }
    std::cout << "Use count of ptr2 is " << ptr2.use_count() << std::endl;

    return 0;
}