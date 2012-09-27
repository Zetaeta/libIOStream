
#ifndef RAWOUTPUTSTREAM_HPP
#define RAWOUTPUTSTREAM_HPP

#include <sys/types.h>

namespace IOStream {

class RawOutputStream {
public:
    virtual ~RawOutputStream() = 0;
    virtual ssize_t write(const void *bytes, size_t size) = 0;
    virtual void close() = 0;
};

}

#endif
