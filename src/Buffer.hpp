
#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <stdint.h>

namespace IOStream {

class Buffer {
public:
    typedef uint8_t *iterator;
    typedef const uint8_t *const_iterator;

    Buffer(size_t length);
    uint8_t take();
    void take(void *output, size_t len);
    size_t request(void *output, size_t len);
    uint8_t * take(size_t len);
    void add(const void *bytes, size_t len);
    size_t offer(const void *bytes, size_t len);
    void add(size_t len);
    iterator begin();
    iterator end();
    iterator trueBegin();
    iterator trueEnd();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator trueBegin() const;
    const_iterator trueEnd() const;
    size_t availableBytes() const;
    size_t available() const;
    size_t spaceAfter() const;
    size_t spaceBefore() const;
    size_t totalSpace() const;
    void shiftToStart();
    size_t fullSize() const;
    uint8_t operator[](size_t) const;

    void resize(size_t newSize);
    off_t seek(off_t pos, int whence);
    
private:
    size_t startPos;
    size_t endPos;
    size_t fullSize_;
    uint8_t *buf;
};

}

#endif
