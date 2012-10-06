
#ifndef MAYBEPOINTER_HPP
#define MAYBEPOINTER_HPP

namespace IOStream {

template <typename T>
class MaybePointer {
public:
    MaybePointer(T *p)
    :ptr(p), isPointer(true) {}

    MaybePointer(T &r)
    :ptr(&r), isPointer(false) {}

    MaybePointer(MaybePointer<T> &&other)
    :ptr(other.ptr), isPointer(other.isPointer) {
        other.isPointer = false;
    }

    MaybePointer(const MaybePointer<T> &other)
    :ptr(other.ptr), isPointer(other.isPointer) {
        other.isPointer = false;
    }

    T & operator*() {
        return *ptr;
    }

    const T & operator*() const {
        return *ptr;
    }

    T * operator->() {
        return ptr;
    }

    const T * operator->() const {
        return ptr;
    }

    operator T*() {
        return ptr;
    }

    operator const T*() const {
        return ptr;
    }

//    operator const T*() const {
//        return ptr;
//    }

    ~MaybePointer() {
        if (isPointer) {
            delete ptr;
        }
    }
private:
    T *ptr;
    mutable bool isPointer; // Must be mutable for modification in copy constructor
};

}

#endif
