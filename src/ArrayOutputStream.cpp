
#include <algorithm>
#include <iostream>

#include "ArrayOutputStream.hpp"


namespace IOStream {

using std::cout;

ArrayOutputStream::ArrayOutputStream(size_t length)
:buffer(length) {}

size_t ArrayOutputStream::size() const {
    return buffer.available();
}

ssize_t ArrayOutputStream::write(const void *out, size_t length) {
    if (buffer.spaceAfter() < length) {
//        cout << "ArrayOutputStream::write(): increasing buffer size.\nTrying to write " << length
//             << " bytes. Current used size: " << buffer.available() << ". Current space after: " << buffer.spaceAfter() << ".\n";
        buffer.resize(buffer.fullSize() + std::max(length, buffer.fullSize() < 128 ? buffer.fullSize() * 2 : size_t(buffer.fullSize() * 1.5)));
//        cout << "New space after: " << buffer.spaceAfter() << ".\n";
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
