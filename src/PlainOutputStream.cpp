
#include <stdio.h>

#include "PlainOutputStream.hpp"

namespace IOStream {

using std::string;

PlainOutputStream::PlainOutputStream(const string &fileName, Endian endian)
:OutputStream(endian), closed(false) {
    file = fopen(fileName.c_str(), "wb");
}

PlainOutputStream::PlainOutputStream(int fd, Endian endian)
:OutputStream(endian), closed(false) {
    file = fdopen(fd, "wb");
}

PlainOutputStream::~PlainOutputStream() {
    if (!closed) {
        close();
    }
}

ssize_t PlainOutputStream::write(const void *bytes, size_t size) {
    size_t result = fwrite(bytes, 1, size, file);
    if (ferror(file)) {
        return -1;
    }
    return result;
}

void PlainOutputStream::seek(size_t offset, int whence) {
    fseek(file, offset, whence);
}

int PlainOutputStream::fd() {
    return fileno(file);
}

void PlainOutputStream::close() {
    closed = true;
    fclose(file);
}

}
