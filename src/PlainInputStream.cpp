
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include "PlainInputStream.hpp"

using std::string;
using std::cout;

namespace IOStream {

PlainInputStream::PlainInputStream(const string &fileName) {
    fd_ = open(fileName.c_str(), O_RDONLY);
    cout << "PlainInputStream(): fd = " << fd_ << '\n';
}

PlainInputStream::PlainInputStream(int fd)
:fd_(fd) {
}

PlainInputStream::~PlainInputStream() {}

ssize_t PlainInputStream::read(void *bytes, size_t size) {
    size_t result = ::read(fd_, bytes, size);
//    if (ferror(file)) {
//        return -1;
//    }
    return result;
}

ssize_t PlainInputStream::peek(void *bytes, size_t size) {
    size_t pos = lseek(fd_, 0, SEEK_CUR);
    ssize_t result = ::read(fd_, bytes, size);
    lseek(fd_, pos, SEEK_SET);
//    if (ferror(file)) {
//        return -1;
//    }
    return result;
}

void PlainInputStream::seek(size_t offset, int whence) {
    lseek(fd_, offset, whence);
}

int PlainInputStream::fd() {
    return fd_;
}

void PlainInputStream::close() {
    ::close(fd_);
}

}
