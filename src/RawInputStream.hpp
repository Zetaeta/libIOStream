
#ifndef RAWINPUTSTREAM_HPP
#define RAWINPUTSTREAM_HPP

#include <sys/types.h>

namespace IOStream {

class RawInputStream {
public:
    virtual ~RawInputStream() = 0;
    virtual ssize_t read(void *bytes, size_t size) = 0;
    virtual void close() = 0;
};

}

#endif
