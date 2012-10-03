
#ifndef MAYBEPOINTER_HPP
#define MAYBEPOINTER_HPP

namespace IOStream {

template <typename T>
class MaybePointer {
public:
    MaybePointer(T *p)
    :ptr(p), ref(*p), isPointer(true) {}
    MaybePointer(T &r)
    :ptr(&r), ref(r), isPointer(false) {}

    T & operator*() {
        return ref;
    }

    const T & operator*() const {
        return ref;
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
    T &ref;
    bool isPointer;
};

}

#endif
