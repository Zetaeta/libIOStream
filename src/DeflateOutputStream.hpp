
#ifndef DEFLATEOUTPUTSTREAM_HPP
#define DEFLATEOUTPUTSTREAM_HPP

#include <string>
#define ZLIB_CONST
#include <zlib.h>

#include "RawOutputStream.hpp"
#include "Buffer.hpp"
#include <Util/MaybePointer.hpp>

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class DeflateOutputStream : public RawOutputStream {
public:
    DeflateOutputStream(const std::string &);
    DeflateOutputStream(int fd);

    DeflateOutputStream(const Util::MaybePointer<RawOutputStream> &);
    ~DeflateOutputStream();

    int fd();

    ssize_t write(const void *bytes, size_t size);
    off_t seek(off_t offset, int whence);
    void finish();
    void close();
private:
    void init();
    void writeBuffer();
    
    z_stream zstream;
    Buffer buffer;
//    int fd_;
    Util::MaybePointer<RawOutputStream> raw;
};

}

#endif // DEFLATEOUTPUTSTREAM_HPP
