
#include <zlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "DeflateInputStream.hpp"

#ifndef DEFLATE_INPUT_STREAM_BUFFER_LENGTH
#define DEFLATE_INPUT_STREAM_BUFFER_LENGTH 256
#endif

namespace IOStream {

using std::string;

DeflateInputStream::DeflateInputStream(const string &fileName, Endian endian)
:InputStream(endian), closed(false), buffer(DEFLATE_INPUT_STREAM_BUFFER_LENGTH) {
    fd_ = open(fileName.c_str(), O_RDONLY);
    init();
}

DeflateInputStream::DeflateInputStream(int fd, Endian endian)
:InputStream(endian), closed(false), fd_(fd), buffer(DEFLATE_INPUT_STREAM_BUFFER_LENGTH) {
    init();
}

DeflateInputStream::~DeflateInputStream() {
    if (!closed) {
        close();
    }
}

void DeflateInputStream::init() {
    zstream.zalloc = NULL;
    zstream.zfree = NULL;
    zstream.opaque = NULL;
    zstream.next_in = buffer.begin();
    zstream.avail_in = 0;
    zstream.next_out = NULL;
    zstream.avail_out = 0;
    zstream.total_in = 0;
    zstream.total_out = 0;
    zstream.data_type = Z_BINARY;
    inflateInit(&zstream);
}

ssize_t DeflateInputStream::read(void *bytes, size_t size) {
    static bool first = true;
    if (first) {
        populateBuffer();
        first = false;
    }
    zstream.next_in = buffer.begin();
    zstream.avail_in = buffer.available();
    zstream.next_out = static_cast<uint8_t *>(bytes);
    zstream.avail_out = size;
    int returned = Z_STREAM_END;
    int inBefore = zstream.avail_in;
    while ((zstream.avail_out != 0) && ((returned = inflate(&zstream, Z_FINISH)) != Z_BUF_ERROR)) { // While there is space in `bytes` and no buffer error.
        buffer.take(inBefore - zstream.avail_in);
        populateBuffer();
        zstream.avail_in = buffer.available();
        zstream.next_in = buffer.begin();
    }
}

void DeflateInputStream::populateBuffer() {
    if (buffer.spaceBefore() > buffer.spaceAfter()) {
        buffer.shiftToStart();
        zstream.next_in = buffer.begin();
    }
    size_t bytesRead = ::read(fd_, buffer.end(), buffer.spaceAfter());
    buffer.add(bytesRead);
    zstream.avail_in = buffer.available();
}

ssize_t DeflateInputStream::peek(void *, size_t) {
    return 0;
}

void DeflateInputStream::seek(size_t offset, int whence) {
    lseek(fd_, offset, whence);
}

int DeflateInputStream::fd() {
    return fd_;
}

void DeflateInputStream::close() {
    closed = true;
    ::close(fd_);
}

}
