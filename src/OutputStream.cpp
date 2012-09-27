
#include <libendian/endian.h>

#include "OutputStream.hpp"

namespace IOStream {

OutputStream::OutputStream(Endian endian) {
    if (endian == NATIVE) {
        swap = false;
    }
    else {
        swap = bigEndian ? (endian == LITTLE) : (endian == BIG);
    }
}

OutputStream & OutputStream::operator<<(int8_t data) {
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(uint8_t data) {
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(int16_t data) {
    if (swap) {
        swapEndian(data);
    }
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(uint16_t data) {
    if (swap) {
        swapEndian(data);
    }
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(int32_t data) {
    if (swap) {
        swapEndian(data);
    }
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(uint32_t data) {
    if (swap) {
        swapEndian(data);
    }
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(int64_t data) {
    if (swap) {
        swapEndian(data);
    }
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(uint64_t data) {
    if (swap) {
        swapEndian(data);
    }
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(float data) {
    if (swap) {
        swapEndian(data);
    }
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(double data) {
    if (swap) {
        swapEndian(data);
    }
    write(&data, sizeof(data));
}

OutputStream & OutputStream::operator<<(const std::string &data) {
    uint16_t length(data.size());
    operator<<(length);
    write(&data[0], length);
}

OutputStream::~OutputStream() {}

}

