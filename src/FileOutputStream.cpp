
#include <unistd.h>
#include <fcntl.h>

#include <Util/ErrorHandler.hpp>

#include "FileOutputStream.hpp"

using Util::throwException;

namespace IOStream {

FileOutputStream::FileOutputStream(const std::string &file) {
    fd_ = open(file.c_str(), O_WRONLY);
}

FileOutputStream::FileOutputStream(int fd)
:fd_(fd) {}

ssize_t FileOutputStream::write(const void *buf, size_t length) {
    int ret = ::write(fd_, buf, length);
    if (ret < 0) {
        throwException(errno);
    }
    return ret;
}

off_t FileOutputStream::seek(off_t offset, int whence) {
    return lseek(fd_, offset, whence);
}

void FileOutputStream::close() {
    ::close(fd_);
}

}

