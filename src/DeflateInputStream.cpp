
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "DeflateInputStream.hpp"
#include "FileInputStream.hpp"

#ifndef DEFLATE_INPUT_STREAM_BUFFER_LENGTH
#define DEFLATE_INPUT_STREAM_BUFFER_LENGTH 256
#endif

using std::string;

namespace IOStream {

DeflateInputStream::DeflateInputStream(const string &filename)
:DeflateInputStream(new FileInputStream(filename)) {
    init();
}

DeflateInputStream::DeflateInputStream(int fd)
:DeflateInputStream(new FileInputStream(fd)) {
    init();
}


DeflateInputStream::DeflateInputStream(const MaybePointer<RawInputStream> &raw)
:buffer(DEFLATE_INPUT_STREAM_BUFFER_LENGTH), raw(raw) {
    init();
}

DeflateInputStream::~DeflateInputStream() {}

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
}

ssize_t DeflateInputStream::read(void *bytes, size_t size) {
//    cout << "DeflateInputStream::read()\n";
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
//        cout << "About to inflate, buffer.available() = " << buffer.available() << '\n';
        returned = inflate(&zstream, Z_SYNC_FLUSH);
//        cout << "Bytes taken: " << (inBefore - zstream.avail_in) << '\n';
        buffer.take(inBefore - zstream.avail_in);
        populateBuffer();
        zstream.avail_in = buffer.available();
        zstream.next_in = buffer.begin();
        inBefore = zstream.avail_in;
/*        if (returned == Z_STREAM_ERROR) {
            cerr << "Z_STREAM_ERROR!\n";
            if (zstream.msg) {
                cerr << "zstream.msg: " << zstream.msg << '\n';
                zstream.msg = NULL;
            }
            cerr << "next_in = " << static_cast<void *>(zstream.next_in) << '\n';
            cerr << "next_out = " << static_cast<void *>(zstream.next_out) << '\n';
        }
        if (returned == Z_BUF_ERROR) {
            cerr << "Z_BUF_ERROR!\n";
            if (zstream.msg) {
                cerr << "zstream.msg: " << zstream.msg << '\n';
            }
            cerr << "next_in = " << static_cast<void *>(zstream.next_in) << '\n';
            cerr << "next_out = " << static_cast<void *>(zstream.next_out) << '\n';
        }
        if (returned == Z_DATA_ERROR) {
//            cerr << "Z_DATA_ERROR!\n";
            if (zstream.msg) {
//                cerr << "zstream.msg: " << zstream.msg << '\n';
            }
        }
        if (returned == Z_MEM_ERROR) {
            cerr << "Z_MEM_ERROR!\n";
            if (zstream.msg) {
                cerr << "zstream.msg: " << zstream.msg << '\n';
            }
            cerr << "next_in = " << static_cast<void *>(zstream.next_in) << '\n';
            cerr << "next_out = " << static_cast<void *>(zstream.next_out) << '\n';
        } */
/*        if (returned != Z_OK) {
            cerr << "returned != Z_OK!\n";
            if (zstream.msg) {
                cerr << "zstream.msg: " << zstream.msg << '\n';
            }
        }*/
        
    }
/*    if (returned == Z_STREAM_ERROR) {
        cerr << "Z_STREAM_ERROR!\n";
        if (zstream.msg) {
            cerr << "zstream.msg: " << zstream.msg << '\n';
        }
        cerr << "next_in = " << static_cast<void *>(zstream.next_in) << '\n';
        cerr << "next_out = " << static_cast<void *>(zstream.next_out) << '\n';
    } */
    return size;
}

void DeflateInputStream::populateBuffer() {
    if (buffer.spaceBefore() > buffer.spaceAfter()) {
        buffer.shiftToStart();
        zstream.next_in = buffer.begin();
    }
    if (buffer.spaceAfter() == 0) {
//        zstream.avail_in = buffer.available();
        return;
    }
    errno = 0;
    ssize_t bytesRead = raw->read(buffer.end(), buffer.spaceAfter());
    if (bytesRead < 0) {
//        cerr << "Error reading: " << strerror(errno) << '\n';
        return;
    }
    buffer.add(size_t(bytesRead));
    zstream.avail_in = buffer.available();
}

ssize_t DeflateInputStream::peek(void *, size_t) {
    return 0;
}

off_t DeflateInputStream::seek(off_t offset, int whence) {
    return raw->seek(offset, whence);
}

// "Put back" what is left in the buffer into the file.
void DeflateInputStream::putBack() {
    raw->seek(-buffer.available(), SEEK_CUR);
}

void DeflateInputStream::finish() {
    populateBuffer();
    inflateEnd(&zstream);
    putBack();
}

void DeflateInputStream::close() {
    finish();
    raw->close();
}

}
