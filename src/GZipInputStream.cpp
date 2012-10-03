
#include <zlib.h>
#include <fcntl.h>

#include "GZipInputStream.hpp"

namespace IOStream {

using std::string;

GZipInputStream::GZipInputStream(const string &fileName) {
    fd_ = open(fileName.c_str(), O_RDONLY);
    file = gzdopen(fd_, "rb");
}

GZipInputStream::GZipInputStream(int fd)
:fd_(fd) {
    file = gzdopen(fd, "rb");
}

GZipInputStream::~GZipInputStream() {}

ssize_t GZipInputStream::read(void *bytes, size_t size) {
    int result = gzread(file, bytes, size);
    int err;
    gzerror(file, &err);
    if (err) {
        return -1;
    }
    return result;
}

ssize_t GZipInputStream::peek(void *, size_t) {
    return 0;
}

void GZipInputStream::seek(size_t offset, int whence) {
    gzseek(file, offset, whence);
}

int GZipInputStream::fd() {
    return fd_;
}

void GZipInputStream::close() {
    gzclose(file);
}

}
