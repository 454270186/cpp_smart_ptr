## 实现类似C++ shared_ptr

**test**

```c++
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
```
**输出**
```
Use count of ptr1 is 1
Use count of ptr2 is 0
Use count of ptr2 is 2
ptr1 is not empty
~circle()
```

### 实现四种强制类型转化
```c++
template <typename T, typename U>
smart_ptr<T> static_pointer_cast(const smart_ptr<U>& other) {
    T* ptr = static_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other) {
    T* ptr = dynamic_cast<T*>(other.get());
    // 这里不能直接用拷贝构造
    // 因为底层U* ptr不能隐式转换为T* ptr
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(const smart_ptr<U>& other) {
    T* ptr = reinterpret_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> const_pointer_cast(const smart_ptr<U>& other) {
    T* ptr = const_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}
```
**test**
```c++
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
```
**输出**
```
Use count of ptr1 is 1
Use count of ptr2 is 0
ptr1 is not empty
Use count of ptr3 is 3
Use count of ptr3 is 4
~circle()
```