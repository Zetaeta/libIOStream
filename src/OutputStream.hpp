
#ifndef OUTPUTSTREAM_HPP
#define OUTPUTSTREAM_HPP

#include <stdint.h>
#include <string>

#include <sys/types.h>

#include "Endian.hpp"
#include <Util/MaybePointer.hpp>

namespace IOStream {

class RawOutputStream;

class OutputStream {
public:
    OutputStream(const Util::MaybePointer<RawOutputStream> & = nullptr, Endian = DEFAULT_ENDIAN);
    OutputStream(const std::string &filename);
    OutputStream(int fd);

    OutputStream & operator=(OutputStream &&other) {
        raw = other.raw;
        return *this;
    }

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
    // See InputStream.
    virtual OutputStream & operator<<(const std::string &);

    void writeByte(int8_t);
    void writeUByte(uint8_t);
    void writeShort(int16_t);
    void writeUShort(uint16_t);
    void writeInt(int32_t);
    void writeUInt(uint32_t);
    void writeLong(int64_t);
    void writeULong(uint64_t);
    void writeFloat(float);
    void writeDouble(double);
    void writeString(const std::string &);

    virtual ~OutputStream();

    ssize_t write(const void *bytes, size_t size);
    off_t seek(off_t offset, int whence);
    void close();
protected:
    Util::MaybePointer<RawOutputStream> raw;
    bool swap;
};

}

#endif // OUTPUTSTREAM_HPP
