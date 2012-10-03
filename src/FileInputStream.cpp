
#include <unistd.h>
#include <fcntl.h>

#include "FileInputStream.hpp"
#include "ErrorHandler.hpp"

namespace IOStream {

FileInputStream::FileInputStream(const std::string &file) {
    fd_ = open(file.c_str(), O_RDONLY);
}

FileInputStream::FileInputStream(int fd)
:fd_(fd) {}

ssize_t FileInputStream::read(void *buf, size_t length) {
    int ret = ::read(fd_, buf, length);
    if (ret < 0) {
        throwException(ret);
    }
    return ret;
}

void FileInputStream::seek(size_t offset, int whence) {
    lseek(fd_, offset, whence);
}

void FileInputStream::close() {
    ::close(fd_);
}

}

