
#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <stdint.h>

namespace IOStream {

class Buffer {
public:
    typedef uint8_t *iterator;
    typedef const uint8_t *const_iterator;

    Buffer(int length);
    uint8_t take();
    void take(uint8_t *output, size_t len);
    size_t request(uint8_t *output, size_t len);
    uint8_t * take(size_t len);
    void add(uint8_t);
    void add(uint8_t *bytes, size_t len);
    size_t offer(uint8_t *bytes, size_t len);
    void add(size_t len);
    iterator begin();
    iterator end();
    iterator trueBegin();
    iterator trueEnd();
    size_t availableBytes();
    size_t available();
    size_t spaceAfter();
    size_t spaceBefore();
    size_t totalSpace();
    void shiftToStart();
    
private:
    size_t startPos;
    size_t endPos;
    size_t fullSize;
    uint8_t *buf;
};

}

#endif
