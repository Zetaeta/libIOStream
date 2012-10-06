
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <iostream>

#include "ArrayInputStream.hpp"

using std::ostringstream;
using std::cout;

namespace IOStream {

ArrayInputStream::ArrayInputStream(void *bytes, size_t length)
:buffer(length) {
//    memcpy(buffer.begin(), bytes, length);
    std::cout << "ArrayInputStream(): length = " << length << '\n';
    buffer.add(bytes, length);
}

ssize_t ArrayInputStream::read(void *out, size_t length) {
    ssize_t ret = buffer.request(out, length);
    cout << "ArrayInputStream::read(): ret = " << ret << '\n';
    cout << "bytes: {";
    for (size_t i=0; i<ret; ++i) {
        cout << uint16_t(static_cast<uint8_t *>(out)[i]) << ", "; 
    }
    cout << "}\n";
    return ret;
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

