
#include <fcntl.h>
#include <unistd.h>

#include "DeflateOutputStream.hpp"
#include "Buffer.hpp"

#ifndef DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH
#define DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH 256
#endif

namespace IOStream {

using std::string;

DeflateOutputStream::DeflateOutputStream(MaybePointer<RawOutputStream> raw)
:buffer(DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH), raw(raw) {}

DeflateOutputStream::~DeflateOutputStream() {}

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
    return size;
}

void DeflateOutputStream::writeBuffer() {
    size_t bytesWritten = raw->write(buffer.begin(), buffer.available());
    buffer.take(bytesWritten);
    zstream.avail_out = buffer.spaceAfter();
    buffer.shiftToStart();
}

void DeflateOutputStream::seek(size_t offset, int whence) {
    raw->seek(offset, whence);
}

void DeflateOutputStream::close() {
    deflateEnd(&zstream);
    raw->close();
}

}
