
#ifndef RAWOUTPUTSTREAM_HPP
#define RAWOUTPUTSTREAM_HPP

#include <stdint.h>
#include <string>

#include <sys/types.h>

#include "Endian.hpp"

namespace IOStream {

class RawOutputStream {
public:
    virtual ~RawOutputStream() = 0;

    virtual ssize_t write(const void *bytes, size_t size) = 0;
    virtual off_t seek(off_t offset, int whence) = 0;
    virtual void close() = 0;
};

}

#endif
