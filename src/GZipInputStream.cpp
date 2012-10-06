
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>

#include "GZipInputStream.hpp"
#include "FileInputStream.hpp"

#ifndef DEFLATE_INPUT_STREAM_BUFFER_LENGTH
#define DEFLATE_INPUT_STREAM_BUFFER_LENGTH 256
#endif

using std::string;
using std::cerr;

namespace IOStream {

GZipInputStream::GZipInputStream(const MaybePointer<RawInputStream> &raw)
:buffer(DEFLATE_INPUT_STREAM_BUFFER_LENGTH), raw(raw) {
    init();
}

GZipInputStream::GZipInputStream(const string &filename)
:GZipInputStream(new FileInputStream(filename)) {
    init();
}

GZipInputStream::GZipInputStream(int fd)
:GZipInputStream(new FileInputStream(fd)) {
    init();
}

GZipInputStream::~GZipInputStream() {}

void GZipInputStream::init() {
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
    int ret = inflateInit2(&zstream, 16 + MAX_WBITS);
    if (ret == Z_OK) {
    }
    else if (ret == Z_STREAM_ERROR) {
        cerr << "init(): Z_STREAM_ERROR\n";
    }
    else {
        cerr << "init(): failure!\n";
    }
}

ssize_t GZipInputStream::read(void *bytes, size_t size) {
    static bool first = true;
    if (first) {
        populateBuffer();
        first = false;
    }
    zstream.next_in = buffer.begin();
    zstream.avail_in = buffer.available();
    zstream.next_out = static_cast<uint8_t *>(bytes);
    zstream.avail_out = size;
    int returned = 0;
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
    return size;
}

void GZipInputStream::populateBuffer() {
    if (buffer.spaceBefore() > buffer.spaceAfter()) {
        buffer.shiftToStart();
        zstream.next_in = buffer.begin();
    }
    if (buffer.spaceAfter() == 0) {
        return;
    }
    errno = 0;
    ssize_t bytesRead = raw->read(buffer.end(), buffer.spaceAfter());
    if (bytesRead < 0) {
        cerr << "Error reading: " << strerror(errno) << '\n';
        return;
    }
    buffer.add(size_t(bytesRead));
    zstream.avail_in = buffer.available();
}

ssize_t GZipInputStream::peek(void *, size_t) {
    return 0;
}

off_t GZipInputStream::seek(off_t offset, int whence) {
    return raw->seek(offset, whence);
}

// "Put back" what is left in the buffer into the file.
void GZipInputStream::putBack() {
    raw->seek(buffer.available(), SEEK_CUR);
}

void GZipInputStream::close() {
    inflateEnd(&zstream);
    putBack();
    raw->close();
}

}
