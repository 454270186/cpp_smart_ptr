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
