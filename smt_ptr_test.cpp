#include <iostream>
#include <algorithm>
#include "smart_ptr.hpp"

class shape {
public:
    virtual ~shape() {};
};

class circle : public shape {
public:
    ~circle() {
        puts("~circle()");
    }
};

int main() {
    smart_ptr<circle> ptr1(new circle());
    printf("Use count of ptr1 is %ld\n", ptr1.use_count());

    smart_ptr<shape> ptr2;
    printf("Use count of ptr2 is %ld\n", ptr2.use_count());

    ptr2 = ptr1;
    printf("Use count of ptr2 is %ld\n", ptr2.use_count());

    if (ptr1) {
        printf("ptr1 is not empty\n");
    }

    // test: dynamic_pointer_cast
    smart_ptr<circle> ptr3 = dynamic_pointer_cast<circle>(ptr2);
    printf("Use count of ptr3 is %ld\n", ptr3.use_count());

    smart_ptr<circle> ptr4 = static_pointer_cast<circle>(ptr2);
    printf("Use count of ptr3 is %ld\n", ptr4.use_count());
}