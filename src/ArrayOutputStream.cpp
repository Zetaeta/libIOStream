
#include "ArrayOutputStream.hpp"

namespace IOStream {

ArrayOutputStream::ArrayOutputStream(size_t length)
:buffer(length) {}

size_t ArrayOutputStream::size() const {
    return buffer.available();
}

ssize_t ArrayOutputStream::write(const void *out, size_t length) {
    if (buffer.spaceAfter() < length) {
        buffer.resize(buffer.fullSize() < 128 ? buffer.fullSize() * 2 : buffer.fullSize() * 1.5);
    }
    buffer.add(out, length);
    return length;
}

off_t ArrayOutputStream::seek(off_t offset, int whence) {
    return buffer.seek(offset, whence);
}

uint8_t * ArrayOutputStream::data() {
    return buffer.begin();
}

void ArrayOutputStream::close() {
}

}
