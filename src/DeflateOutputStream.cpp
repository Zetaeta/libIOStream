
#include <fcntl.h>
#include <unistd.h>

#include "DeflateOutputStream.hpp"
#include "Buffer.hpp"

#ifndef DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH
#define DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH 256
#endif

namespace IOStream {

using std::string;

DeflateOutputStream::DeflateOutputStream(const string &fileName, Endian endian)
:OutputStream(endian), closed(false), buffer(DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH) {
    fd_ = open(fileName.c_str(), O_RDONLY);
    init();
}

DeflateOutputStream::DeflateOutputStream(int fd, Endian endian)
:OutputStream(endian), closed(false), fd_(fd), buffer(DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH) {
    init();
}

DeflateOutputStream::~DeflateOutputStream() {
    if (!closed) {
        close();
    }
}

void DeflateOutputStream::init() {
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
    deflateInit(&zstream, Z_DEFAULT_COMPRESSION);
}

ssize_t DeflateOutputStream::write(const void *bytes, size_t size) {
    zstream.next_out = buffer.end();
    zstream.avail_out = buffer.spaceAfter();
    zstream.next_in = static_cast<uint8_t *>(const_cast<void *>(bytes));
    zstream.avail_in = size;
    int returned = Z_STREAM_END;
    int outBefore = zstream.avail_out;
    while ((zstream.avail_in != 0) && ((returned = deflate(&zstream, Z_FINISH)) != Z_BUF_ERROR)) { // While there is space in `bytes` and no buffer error.
        buffer.add(size_t(outBefore - zstream.avail_out));
        writeBuffer();
        zstream.next_out = buffer.end();
    }
}

void DeflateOutputStream::writeBuffer() {
    size_t bytesWritten = ::write(fd_, buffer.begin(), buffer.available());
    buffer.take(bytesWritten);
    zstream.avail_out = buffer.spaceAfter();
    buffer.shiftToStart();
}

void DeflateOutputStream::seek(size_t offset, int whence) {
    lseek(fd_, offset, whence);
}

int DeflateOutputStream::fd() {
    return fd_;
}

void DeflateOutputStream::close() {
    closed = true;
    ::close(fd_);
}

}
