
#include <unistd.h>
#include <fcntl.h>
#include <sstream>

#include <Util/ErrorHandler.hpp>

#include "FileIOStream.hpp"

namespace IOStream {

using std::string;

FileIOStream::FileIOStream(const string &file) {
    fd_ = open(file.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd_ < 0) {
        throwException(errno, file);
    }
}

ssize_t FileIOStream::read(void *out, size_t length) {
    ssize_t ret = ::read(fd_, out, length);
    if (ret < 0) {
        throwException(errno);
    }
    return ret;
}

ssize_t FileIOStream::peek(void *buf, size_t length) {
    off_t offset = lseek(fd_, 0, SEEK_CUR);
    ssize_t ret = read(buf, length);
    lseek(fd_, offset, SEEK_SET);
    return ret;
}

off_t FileIOStream::seek(off_t offset, int whence) {
    return lseek(fd_, offset, whence);
}

ssize_t FileIOStream::write(const void *buf, size_t length) {
    int ret = ::write(fd_, buf, length);
    if (ret < 0) {
        throwException(errno);
    }
    return ret;
}

void FileIOStream::close() {
    ::close(fd_);
}

}
