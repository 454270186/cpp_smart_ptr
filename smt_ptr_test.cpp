#include <iostream>
#include <algorithm>
#include <memory>
#include "smart_ptr.hpp"

class shape {
public:
    virtual ~shape() {}
};

class circle : public shape {
public:
    ~circle() {
        puts("~circle()");
    }
};

int main() {
    // smart_ptr<circle> ptr1(new circle());
    // printf("Use count of ptr1 is %ld\n", ptr1.use_count());

    // smart_ptr<shape> ptr2;
    // printf("Use count of ptr2 is %ld\n", ptr2.use_count());

    // ptr2 = ptr1;
    // printf("Use count of ptr2 is %ld\n", ptr2.use_count());

    // if (ptr1) {
    //     printf("ptr1 is not empty\n");
    // }

    // ptr1.reset();
    // if (!ptr1) {
    //     printf("ptr1 is empty\n");
    // }

    // printf("Use count of ptr2 is %ld\n", ptr2.use_count());
    // return 0;
    std::shared_ptr<circle> sp1(new circle());
    printf("Use count of sp1 is %ld\n", sp1.use_count());

    std::shared_ptr<shape> sp2 = std::make_shared<shape>();
    printf("Use count of sp2 is %ld\n", sp2.use_count());

    sp2 = sp1;
    printf("Use count of sp2 is %ld\n", sp2.use_count());

    if (sp1) {
        printf("sp1 is not empty\n");
    }

    sp1.reset();
    if (!sp1) {
        printf("sp1 is empty\n");
    }

    printf("Use count of sp2 is %ld\n", sp2.use_count());
    return 0;
}