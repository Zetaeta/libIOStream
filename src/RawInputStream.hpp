
#ifndef RAWINPUTSTREAM_HPP
#define RAWINPUTSTREAM_HPP

#include <stdint.h>
#include <string>

#include <sys/types.h>

#include "Endian.hpp"

namespace IOStream {

class RawInputStream {
public:
    virtual ~RawInputStream() = 0;

    virtual ssize_t read(void *, size_t length) = 0;
    virtual ssize_t peek(void *, size_t length) = 0;
    virtual void seek(size_t offset, int whence) = 0;
    virtual void close() = 0;
};

}

#endif
