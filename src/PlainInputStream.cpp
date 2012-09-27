
#include <stdio.h>

#include "PlainInputStream.hpp"

namespace IOStream {

using std::string;

PlainInputStream::PlainInputStream(const string &fileName, Endian endian)
:InputStream(endian), closed(false) {
    file = fopen(fileName.c_str(), "rb");
}

PlainInputStream::PlainInputStream(int fd, Endian endian)
:InputStream(endian), closed(false) {
    file = fdopen(fd, "rb");
}

PlainInputStream::~PlainInputStream() {
    if (!closed) {
        close();
    }
}

ssize_t PlainInputStream::read(void *bytes, size_t size) {
    size_t result = fread(bytes, 1, size, file);
    if (ferror(file)) {
        return -1;
    }
    return result;
}

ssize_t PlainInputStream::peek(void *bytes, size_t size) {
    size_t pos = ftell(file);
    size_t result = fread(bytes, 1, size, file);
    fseek(file, pos, SEEK_SET);
    if (ferror(file)) {
        return -1;
    }
    return result;
}

void PlainInputStream::seek(size_t offset, int whence) {
    fseek(file, offset, whence);
}

int PlainInputStream::fd() {
    return fileno(file);
}

void PlainInputStream::close() {
    closed = true;
    fclose(file);
}

}
