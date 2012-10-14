
#include <fcntl.h>
#include <unistd.h>

#include "GZipOutputStream.hpp"
#include "FileOutputStream.hpp"

#ifndef DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH
#define DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH 256
#endif

using std::string;

using Util::MaybePointer;

namespace IOStream {

GZipOutputStream::GZipOutputStream(const MaybePointer<RawOutputStream> &raw)
:buffer(DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH), raw(raw) {}

GZipOutputStream::GZipOutputStream(const string &filename)
:GZipOutputStream(new FileOutputStream(filename)) {}

GZipOutputStream::GZipOutputStream(int fd)
:GZipOutputStream(new FileOutputStream(fd)) {}

GZipOutputStream::~GZipOutputStream() {}

void GZipOutputStream::init() {
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
    deflateInit2(&zstream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 16 + MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY);
}

ssize_t GZipOutputStream::write(const void *bytes, size_t size) {
    zstream.next_out = buffer.end();
    zstream.avail_out = buffer.spaceAfter();
    zstream.next_in = static_cast<uint8_t *>(const_cast<void *>(bytes));
    zstream.avail_in = size;
//    int returned = Z_STREAM_END;
    int outBefore = zstream.avail_out;
    while ((zstream.avail_in != 0)) { // While there is space in `bytes` and no buffer error.
        deflate(&zstream, Z_SYNC_FLUSH);
        buffer.add(size_t(outBefore - zstream.avail_out));
        writeBuffer();
        zstream.next_out = buffer.end();
    }
    return size;
}

void GZipOutputStream::writeBuffer() {
    size_t bytesWritten = raw->write(buffer.begin(), buffer.available());
    buffer.take(bytesWritten);
    zstream.avail_out = buffer.spaceAfter();
    buffer.shiftToStart();
}

off_t GZipOutputStream::seek(off_t offset, int whence) {
    return raw->seek(offset, whence);
}

void GZipOutputStream::close() {
    deflateEnd(&zstream);
    raw->close();
}

}
