
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>

#include "FileInputStream.hpp"
#include "ErrorHandler.hpp"

using std::cout;

namespace IOStream {

FileInputStream::FileInputStream(const std::string &file) {
    fd_ = open(file.c_str(), O_RDONLY);
    if (fd_ < 0) {
        throwException(errno);
    }
}

FileInputStream::FileInputStream(int fd)
:fd_(fd) {}

ssize_t FileInputStream::read(void *out, size_t length) {
    ssize_t ret = ::read(fd_, out, length);
    if (ret < 0) {
        throwException(errno);
    }
    std::cout << "FileInputStream::read(): ret = " << ret << '\n';
    cout << "bytes: {";
    for (size_t i=0; i<ret; ++i) {
        cout << uint16_t(static_cast<uint8_t *>(out)[i]) << ", "; 
    }
    cout << "}\n";
    return ret;
}

ssize_t FileInputStream::peek(void *buf, size_t length) {
    off_t offset = lseek(fd_, 0, SEEK_CUR);
    ssize_t ret = read(buf, length);
    lseek(fd_, offset, SEEK_SET);
    return ret;
}

off_t FileInputStream::seek(off_t offset, int whence) {
    return lseek(fd_, offset, whence);
}

void FileInputStream::close() {
    ::close(fd_);
}

}

