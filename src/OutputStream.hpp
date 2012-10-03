
#ifndef OUTPUTSTREAM_HPP
#define OUTPUTSTREAM_HPP

#include <stdint.h>
#include <string>

#include <sys/types.h>

#include "Endian.hpp"
#include "MaybePointer.hpp"

namespace IOStream {

class RawOutputStream;

class OutputStream {
public:
    OutputStream(MaybePointer<RawOutputStream>, Endian = DEFAULT_ENDIAN);
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
    virtual ~OutputStream();

    ssize_t write(const void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    MaybePointer<RawOutputStream> raw;
    bool swap;
};

}

#endif // OUTPUTSTREAM_HPP
