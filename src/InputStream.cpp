
#include <sstream>

#include <Util/Endian.h>

#include "InputStream.hpp"
#include "RawInputStream.hpp"
#include "FileInputStream.hpp"

using std::string;

using Util::MaybePointer;

namespace IOStream {

InputStream::InputStream(const MaybePointer<RawInputStream> &raw, Endian endian)
:raw(raw) {
    if (endian == NATIVE) {
        swap = false;
    }
    else {
        swap = bigEndian ? (endian == LITTLE) : (endian == BIG);
    }
}

InputStream::InputStream(const std::string &filename)
:InputStream(new FileInputStream(filename)) {}

InputStream::InputStream(int fd)
:InputStream(new FileInputStream(fd)) {}

InputStream & InputStream::operator>>(int8_t &data) {
    raw->read(&data, sizeof(data));
    return *this;
}

InputStream & InputStream::operator>>(uint8_t &data) {
    raw->read(&data, sizeof(data));
    return *this;
}

InputStream & InputStream::operator>>(int16_t &data) {
    raw->read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
    return *this;
}

InputStream & InputStream::operator>>(uint16_t &data) {
    raw->read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
    return *this;
} 
InputStream & InputStream::operator>>(int32_t &data) {
    raw->read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
    return *this;
}

InputStream & InputStream::operator>>(uint32_t &data) {
    raw->read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
    return *this;
}

InputStream & InputStream::operator>>(int64_t &data) {
    raw->read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
    return *this;
}

InputStream & InputStream::operator>>(uint64_t &data) {
    raw->read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
    return *this;
}

InputStream & InputStream::operator>>(float &data) {
    raw->read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
    return *this;
}

InputStream & InputStream::operator>>(double &data) {
    raw->read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
    return *this;
}

InputStream & InputStream::operator>>(std::string &data) {
    uint16_t length;
    operator>>(length);
    std::stringstream ss;
    for (int i=0; i<length; ++i) {
        char ch;
        raw->read(&ch, 1);
        ss << ch;
    }
    data = ss.str();
    return *this;
}

int8_t InputStream::readByte() {
    int8_t i;
    operator>>(i);
    return i;
}

uint8_t InputStream::readUByte() {
    uint8_t i;
    operator>>(i);
    return i;
}

int16_t InputStream::readShort() {
    int16_t i;
    operator>>(i);
    return i;
}

uint16_t InputStream::readUShort() {
    uint16_t i;
    operator>>(i);
//    operator>>(i);
    return i;
}

int32_t InputStream::readInt() {
    int32_t i;
    operator>>(i);
    return i;
}

uint32_t InputStream::readUInt() {
    uint32_t i;
    operator>>(i);
    return i;
}

int64_t InputStream::readLong() {
    int64_t i;
    operator>>(i);
    return i;
}

uint64_t InputStream::readULong() {
    uint64_t i;
    operator>>(i);
    return i;
}

float InputStream::readFloat() {
    float f;
    operator>>(f);
    return f;
}

double InputStream::readDouble() {
    double d;
    operator>>(d);
    return d;
}

string InputStream::readString() {
    string s;
    operator>>(s);
    return s;
}

ssize_t InputStream::read(void *buf, size_t length) {
    return raw->read(buf, length);
}

ssize_t InputStream::peek(void *buf, size_t length) {
    return raw->peek(buf, length);
}

off_t InputStream::seek(off_t offset, int whence) {
    return raw->seek(offset, whence);
}

void InputStream::close() {
    raw->close();
}

InputStream::~InputStream() {
}

}

