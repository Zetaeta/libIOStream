
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>

#include "DeflateInputStream.hpp"

#ifndef DEFLATE_INPUT_STREAM_BUFFER_LENGTH
#define DEFLATE_INPUT_STREAM_BUFFER_LENGTH 256
#endif

using std::string;
using std::cerr;

namespace IOStream {

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
    int ret = inflateInit(&zstream);
    if (ret == Z_OK) {
    }
    else if (ret == Z_STREAM_ERROR) {
        cerr << "init(): Z_STREAM_ERROR\n";
    }
    else {
        cerr << "init(): failure!\n";
    }
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
    int returned;
    int inBefore = zstream.avail_in;
    while ((zstream.avail_out != 0)) { // While there is space in `bytes` and no buffer error.
        returned = inflate(&zstream, Z_SYNC_FLUSH);
        buffer.take(inBefore - zstream.avail_in);
        populateBuffer();
        zstream.avail_in = buffer.available();
        zstream.next_in = buffer.begin();
        inBefore = zstream.avail_in;
    }
    if (returned == Z_STREAM_ERROR) {
        cerr << "Z_STREAM_ERROR!\n";
        if (zstream.msg) {
            cerr << "zstream.msg: " << zstream.msg << '\n';
        }
        cerr << "next_in = " << static_cast<void *>(zstream.next_in) << '\n';
        cerr << "next_out = " << static_cast<void *>(zstream.next_out) << '\n';
    }
}

void DeflateInputStream::populateBuffer() {
    if (buffer.spaceBefore() > buffer.spaceAfter()) {
        buffer.shiftToStart();
        zstream.next_in = buffer.begin();
    }
    errno = 0;
    ssize_t bytesRead = ::read(fd_, buffer.end(), buffer.spaceAfter());
    if (bytesRead < 0) {
        cerr << "Error reading: " << strerror(errno) << '\n';
        return;
    }
    buffer.add(size_t(bytesRead));
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

// "Put back" what is left in the buffer into the file.
void DeflateInputStream::putBack() {
    lseek(fd_, buffer.available(), SEEK_CUR);
}

void DeflateInputStream::close() {
    closed = true;
    ::close(fd_);
    inflateEnd(&zstream);
    putBack();
}

}
