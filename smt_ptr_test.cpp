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

}