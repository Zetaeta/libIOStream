
#include <sstream>

#include <libendian/endian.h>

#include "InputStream.hpp"

using std::string;

namespace IOStream {

InputStream::InputStream(Endian endian) {
    if (endian == NATIVE) {
        swap = false;
    }
    else {
        swap = bigEndian ? (endian == LITTLE) : (endian == BIG);
    }
}

InputStream & InputStream::operator>>(int8_t &data) {
    read(&data, sizeof(data));
}
InputStream & InputStream::operator>>(uint8_t &data) {
    read(&data, sizeof(data));
}

InputStream & InputStream::operator>>(int16_t &data) {
    read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
}

InputStream & InputStream::operator>>(uint16_t &data) {
    read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    } } 
InputStream & InputStream::operator>>(int32_t &data) {
    read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
}

InputStream & InputStream::operator>>(uint32_t &data) {
    read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
}

InputStream & InputStream::operator>>(int64_t &data) {
    read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
}

InputStream & InputStream::operator>>(uint64_t &data) {
    read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
}

InputStream & InputStream::operator>>(float &data) {
    read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
}

InputStream & InputStream::operator>>(double &data) {
    read(&data, sizeof(data));
    if (swap) {
        swapEndian(data);
    }
}

InputStream & InputStream::operator>>(std::string &data) {
    uint16_t length;
    operator>>(length);
    std::stringstream ss;
    for (int i=0; i<length; ++i) {
        char ch;
        read(&ch, 1);
        ss << ch;
    }
    data = ss.str();
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


InputStream::~InputStream() {}

}

