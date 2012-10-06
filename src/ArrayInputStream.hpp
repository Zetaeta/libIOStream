
#ifndef ARRAYINPUTSTREAM_HPP
#define ARRAYINPUTSTREAM_HPP

#include "RawInputStream.hpp"
#include "Buffer.hpp"

namespace IOStream {

class ArrayInputStream : public RawInputStream {
public:
    ArrayInputStream(void *bytes, size_t length);
    size_t size() const;

    ssize_t read(void *out, size_t length);
    ssize_t peek(void *out, size_t length);
    off_t seek(off_t offset, int whence);
    void close();
private:
    Buffer buffer;
};

}

#endif
