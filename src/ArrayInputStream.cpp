
#include <sstream>
#include <stdexcept>
#include <string.h>

#include "ArrayInputStream.hpp"

using std::ostringstream;

namespace IOStream {

ArrayInputStream::ArrayInputStream(void *bytes, size_t length)
:buffer(length) {
//    memcpy(buffer.begin(), bytes, length);
    buffer.add(bytes, length);
}

ssize_t ArrayInputStream::read(void *out, size_t length) {
    return buffer.request(out, length);
}

ssize_t ArrayInputStream::peek(void *out, size_t length) {
    if (length > buffer.available()) {
        length = buffer.available();
//        ostringstream ss;
//        ss << "ArrayInputStream::peek(): " << length << " > " << buffer.available() << '\n';
//        throw std::underflow_error(ss.str());
    }
    memcpy(buffer.begin(), out, length);
    return length;
}

off_t ArrayInputStream::seek(off_t offset, int whence) {
    return buffer.seek(offset, whence);
}

void ArrayInputStream::close() {}

}

