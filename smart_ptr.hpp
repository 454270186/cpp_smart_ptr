#ifndef _SMART_PTR
#define _SMART_PTR
#include <algorithm>

class shared_count {
public:
    shared_count() : count_(1) {};
    void add_count() {
        count_++;
    }
    long reduce_count() {
        return --count_;
    }
    long get_count() const {
        return count_;
    }

private:
    long count_;
};


template <typename T>
class smart_ptr {
public:
    template <typename U>
    friend class smart_ptr;

    explicit smart_ptr(T* ptr = nullptr) : ptr_(ptr) {
        if (ptr) {
            shared_cnt_ = new shared_count();
        }
    }

    smart_ptr(const smart_ptr& other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_cnt_->add_count();
            shared_cnt_ = other.shared_cnt_;
        }
    }

    smart_ptr(smart_ptr&& other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_cnt_ = other.shared_cnt_;
            other.ptr_ = nullptr;
        }
    }

    // 使子类指针可以转化为基类指针
    template <typename U>
    smart_ptr(const smart_ptr<U>& other) noexcept {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_cnt_->add_count();
            shared_cnt_ = other.shared_cnt_;
        }
    }

    template <typename U>
    smart_ptr(smart_ptr<U>&& other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_cnt_ = other.shared_cnt_;
            other.ptr_ = nullptr;
        }
    }

    // 实现对内部指针赋值时，使用一个现有的共享计数
    // 为了更方便实现dynamic_pointer_cast
    template <typename U>
    smart_ptr(const smart_ptr<U>& other, T* ptr) {
        ptr_ = ptr;
        if (ptr_) {
            other.shared_cnt_->add_count();
            shared_cnt_ = other.shared_cnt_;
        }
    }

    ~smart_ptr() {
        if (ptr_ && !shared_cnt_->reduce_count()){
            delete shared_cnt_;
            delete ptr_;
        }
    }

    T* get() const { return ptr_; }

    long use_count() {
        if (ptr_) {
            return shared_cnt_->get_count();
        } else {
            return 0;
        }
    }

    // overload operator
    T& operator *() { return *ptr_; }
    T* operator ->() { return ptr_; }
    operator bool() { return ptr_ != nullptr; }
    smart_ptr& operator=(smart_ptr rhs) {
        smart_ptr(rhs).swap(*this);
        return *this;
    }
    
    void swap(smart_ptr& rhs) {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(shared_cnt_, rhs.shared_cnt_);
    }

private:
    T* ptr_;
    shared_count* shared_cnt_;
};

template <typename T>
void swap(const smart_ptr<T>& lhs, const smart_ptr<T>& rhs) {
    lhs.swap(rhs);
}

// 实现四种类型转换
// 将类型U转换为类型T
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


#endif