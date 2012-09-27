
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
using std::cout;
using std::cerr;

namespace IOStream {

DeflateInputStream::DeflateInputStream(const string &fileName, Endian endian)
:InputStream(endian), closed(false), buffer(DEFLATE_INPUT_STREAM_BUFFER_LENGTH) {
    fd_ = open(fileName.c_str(), O_RDONLY);
    cout << "DeflateInputStream(): fd = " << fd_ << '\n';
    init();
}

DeflateInputStream::DeflateInputStream(int fd, Endian endian)
:InputStream(endian), closed(false), fd_(fd), buffer(DEFLATE_INPUT_STREAM_BUFFER_LENGTH) {
    cout << "DeflateInputStream(): fd = " << fd_ << '\n';
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
        cout << "init(): Z_OK\n";
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
    cout << "DeflateInputStream::read(): reading " << size << " bytes.\n";
    cout << "buffer.available(): " << buffer.available() << '\n';
    zstream.next_in = buffer.begin();
    zstream.avail_in = buffer.available();
    zstream.next_out = static_cast<uint8_t *>(bytes);
    zstream.avail_out = size;
    int returned;
    int inBefore = zstream.avail_in;
    cout << "About to read, buffer.available() = " << buffer.available() << '\n';
    cout << "next_in = " << static_cast<void *>(zstream.next_in) << '\n';
    cout << "next_out = " << static_cast<void *>(zstream.next_out) << '\n';
    while ((zstream.avail_out != 0)) { // While there is space in `bytes` and no buffer error.
        returned = inflate(&zstream, Z_SYNC_FLUSH);
        cout << "inBefore: " << inBefore << '\n';
        cout << "zstream.avail_in: " << zstream.avail_in << '\n';
        cout << "zstream.avail_out: " << zstream.avail_out << '\n';
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
    cout << "Read bytes: ( ";
    for (size_t i=0; i<size; ++i) {
        cout << uint16_t(static_cast<uint8_t *>(bytes)[i]) << " ";
    }
    cout << ")\n";
}

void DeflateInputStream::populateBuffer() {
    cout << "DeflateInputStream::populateBuffer(): Before reading. buffer.available() = " << buffer.available() << '\n';
    cout << "    buffer.spaceAfter() = " << buffer.spaceAfter() << '\n';
    if (buffer.spaceBefore() > buffer.spaceAfter()) {
        cout << "Shifting to start!\n";
        buffer.shiftToStart();
        zstream.next_in = buffer.begin();
    }
    errno = 0;
    ssize_t bytesRead = ::read(fd_, buffer.end(), buffer.spaceAfter());
    if (bytesRead < 0) {
        cerr << "Error reading: " << strerror(errno) << '\n';
        return;
    }
    cout << "    Read " << bytesRead << " bytes.\n";
    buffer.add(size_t(bytesRead));
    cout << "    After reading. buffer.available() = " << buffer.available() << '\n';
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
