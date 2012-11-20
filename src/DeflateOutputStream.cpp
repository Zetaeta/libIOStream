
#include <fcntl.h>
#include <unistd.h>

#include "DeflateOutputStream.hpp"
#include "Buffer.hpp"
#include "FileOutputStream.hpp"

#ifndef DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH
#define DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH 512
#endif

using std::string;

using Util::MaybePointer;

namespace IOStream {

DeflateOutputStream::DeflateOutputStream(const string &filename)
:DeflateOutputStream(new FileOutputStream(filename)) {
    init();
}

DeflateOutputStream::DeflateOutputStream(int fd)
:DeflateOutputStream(new FileOutputStream(fd)) {
    init();
}

DeflateOutputStream::DeflateOutputStream(const MaybePointer<RawOutputStream> &raw)
:buffer(DEFLATE_OUTPUT_STREAM_BUFFER_LENGTH), raw(raw) {
    init();
}

DeflateOutputStream::~DeflateOutputStream() {}

void DeflateOutputStream::init() {
    zstream.zalloc = NULL;
    zstream.zfree = NULL;
    zstream.opaque = NULL;
    zstream.next_in = NULL;
    zstream.avail_in = 0;
    zstream.next_out = buffer.end();
    zstream.avail_out = 0;
    zstream.total_in = 0;
    zstream.total_out = 0;
    zstream.data_type = Z_BINARY;
    /*int returned = */deflateInit(&zstream, Z_DEFAULT_COMPRESSION);
    
}

ssize_t DeflateOutputStream::write(const void *bytes, size_t size) {
//    cout << "DeflateOutputStream::write(size = " << size << ")\n";
    zstream.next_out = buffer.end();
    zstream.avail_out = buffer.spaceAfter();
    zstream.next_in = static_cast<const uint8_t *>(bytes);
    zstream.avail_in = size;
//    int returned = Z_STREAM_END;
    size_t outBefore = zstream.avail_out;
    size_t lastOut = 0;
    while (zstream.avail_in != 0 || lastOut == 0) { // While there is space in `bytes` and no buffer error.
//        cout << "zstream.avail_out = " << zstream.avail_out << '\n';
//        cout << "zstream.avail_in = " << zstream.avail_in << '\n';
        int returned = deflate(&zstream, Z_SYNC_FLUSH);
//        cout << "outBefore = " << outBefore << '\n';
//        cout << "zstream.avail_out = " << zstream.avail_out << '\n';
//        cout << "zstream.avail_in = " << zstream.avail_in << '\n';
//        cout << "zstream.next_out = " << (void *)zstream.next_out << '\n';
//        cout << "zstream.next_in = " << (void *)zstream.next_in << '\n';
        if (returned != Z_OK) {
//            cout << "returned != Z_OK\n";
            if (zstream.msg) {
//                cout << "zstream.msg: " << zstream.msg << '\n';
//                zstream.msg = nullptr;
            }
/*            switch (returned) {
#undef CASE
            #define CASE(x) case x:\
                cout << #x << '\n';\
                break;
//                cout << "zstream.next_out = " << (void *)zstream.next_out << '\n';
//                cout << "zstream.next_in = " << (void *)zstream.next_in << '\n';
            CASE(Z_STREAM_ERROR)
            CASE(Z_BUF_ERROR)
            CASE(Z_MEM_ERROR)
            }*/
        }
//        cout << "outBefore = " << outBefore << '\n';
//        cout << "zstream.avail_out = " << zstream.avail_out << '\n';
//        cout << "outBefore - zstream.avail_out = " << (outBefore - zstream.avail_out) << '\n';
        buffer.add(size_t(outBefore - zstream.avail_out));
        lastOut = zstream.avail_out;
        writeBuffer();
        outBefore = zstream.avail_out;
        zstream.next_out = buffer.end();
    }
    return size;
}

void DeflateOutputStream::writeBuffer() {
//    cout << "DeflateOutputStream::writeBuffer(): " << buffer.available() << '\n';
    if (buffer.available()) {
        size_t bytesWritten = raw->write(buffer.begin(), buffer.available());
        buffer.take(bytesWritten);
    }
    buffer.shiftToStart();
    zstream.avail_out = buffer.spaceAfter();
}

off_t DeflateOutputStream::seek(off_t offset, int whence) {
    return raw->seek(offset, whence);
}

void DeflateOutputStream::finish() {
    writeBuffer(); // Flush buffer.
    zstream.avail_out = buffer.spaceAfter();
    zstream.next_out = buffer.begin();
    deflateEnd(&zstream);
    buffer.add(buffer.spaceAfter() - zstream.avail_out); // update buffer pos after deflateEnd
    writeBuffer(); // Flush output of deflateEnd from buffer.
}

void DeflateOutputStream::close() {
    finish();
    raw->close();
}

}
