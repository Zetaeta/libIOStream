
#ifndef OUTPUTSTREAM_HPP
#define OUTPUTSTREAM_HPP

#include <stdint.h>
#include <string>

#include <sys/types.h>

#include "Endian.hpp"

namespace IOStream {

class OutputStream {
public:
    OutputStream(Endian = NATIVE);
    OutputStream & operator<<(int8_t);
    OutputStream & operator<<(uint8_t);
    OutputStream & operator<<(int16_t);
    OutputStream & operator<<(uint16_t);
    OutputStream & operator<<(int32_t);
    OutputStream & operator<<(uint32_t);
    OutputStream & operator<<(int64_t);
    OutputStream & operator<<(uint64_t);
    OutputStream & operator<<(float);
    OutputStream & operator<<(double);
    OutputStream & operator<<(const std::string &);
    virtual ~OutputStream() = 0;

    virtual int fd() = 0;

    virtual ssize_t write(const void *bytes, size_t size) = 0;
    virtual void seek(size_t offset, int whence) = 0;
    virtual void close() = 0;
private:
    bool swap;
};

}

#endif // OUTPUTSTREAM_HPP
