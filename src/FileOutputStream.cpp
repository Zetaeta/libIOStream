
#include <unistd.h>
#include <fcntl.h>

#include "FileOutputStream.hpp"
#include "ErrorHandler.hpp"

namespace IOStream {

FileOutputStream::FileOutputStream(const std::string &file) {
    fd_ = open(file.c_str(), O_RDONLY);
}

FileOutputStream::FileOutputStream(int fd)
:fd_(fd) {}

ssize_t FileOutputStream::write(const void *buf, size_t length) {
    int ret = ::write(fd_, buf, length);
    if (ret < 0) {
        throwException(ret);
    }
    return ret;
}

void FileOutputStream::seek(size_t offset, int whence) {
    lseek(fd_, offset, whence);
}

void FileOutputStream::close() {
    ::close(fd_);
}

}

