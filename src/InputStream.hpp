
#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP

#include <stdint.h>
#include <string>

#include <sys/types.h>

#include "Endian.hpp"
#include "MaybePointer.hpp"

namespace IOStream {

class RawInputStream;

class InputStream {
public:
    InputStream(MaybePointer<RawInputStream>, Endian = DEFAULT_ENDIAN);
    InputStream & operator>>(int8_t &);
    InputStream & operator>>(uint8_t &);
    InputStream & operator>>(int16_t &);
    InputStream & operator>>(uint16_t &);
    InputStream & operator>>(int32_t &);
    InputStream & operator>>(uint32_t &);
    InputStream & operator>>(int64_t &);
    InputStream & operator>>(uint64_t &);
    InputStream & operator>>(float &);
    InputStream & operator>>(double &);
    InputStream & operator>>(std::string &);

    int8_t readByte();
    uint8_t readUByte();
    int16_t readShort();
    uint16_t readUShort();
    int32_t readInt();
    uint32_t readUInt();
    int64_t readLong();
    uint64_t readULong();
    float readFloat();
    double readDouble();
    std::string readString();

    InputStream & peek(int8_t &);
    InputStream & peek(uint8_t &);
    InputStream & peek(int16_t &);
    InputStream & peek(uint16_t &);
    InputStream & peek(int32_t &);
    InputStream & peek(uint32_t &);
    InputStream & peek(int64_t &);
    InputStream & peek(uint64_t &);
    InputStream & peek(float &);
    InputStream & peek(double &);
    InputStream & peek(std::string &);
    virtual ~InputStream();

    ssize_t read(void *, size_t);
    ssize_t peek(void *, size_t);
    void seek(size_t offset, int whence);
    void close();

private:
    MaybePointer<RawInputStream> raw;
    bool swap;
};

}

#endif
