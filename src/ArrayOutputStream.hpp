
#ifndef ARRAYOUTPUTSTREAM_HPP
#define ARRAYOUTPUTSTREAM_HPP

#include "RawOutputStream.hpp"
#include "Buffer.hpp"

namespace IOStream {

class ArrayOutputStream : public RawOutputStream {
public:
    ArrayOutputStream(size_t length);
    size_t size() const;
    ssize_t write(const void *out, size_t length);
    off_t seek(off_t offset, int whence);
    void close();
private:
    Buffer buffer;
};

}

#endif
