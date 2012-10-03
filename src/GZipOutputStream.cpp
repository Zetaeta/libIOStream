
#include <zlib.h>
#include <fcntl.h>

#include "GZipOutputStream.hpp"

namespace IOStream {

using std::string;

GZipOutputStream::GZipOutputStream(const string &fileName) {
    fd_ = open(fileName.c_str(), O_WRONLY);
    file = gzdopen(fd_, "wb");
}

GZipOutputStream::GZipOutputStream(int fd)
:fd_(fd) {
    file = gzdopen(fd, "wb");
}

GZipOutputStream::~GZipOutputStream() {}

ssize_t GZipOutputStream::write(const void *bytes, size_t size) {
    int result = gzwrite(file, bytes, size);
    int err;
    gzerror(file, &err);
    if (err) {
        return -1;
    }
    return result;
}

void GZipOutputStream::seek(size_t offset, int whence) {
    gzseek(file, offset, whence);
}

int GZipOutputStream::fd() {
    return fd_;
}

void GZipOutputStream::close() {
    gzclose(file);
}

}
