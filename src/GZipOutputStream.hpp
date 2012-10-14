
#ifndef GZIPOUTPUTSTREAM_HPP
#define GZIPOUTPUTSTREAM_HPP

#include <string>
#include <zlib.h>

#include "RawOutputStream.hpp"
#include "Buffer.hpp"
#include <Util/MaybePointer.hpp>

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class GZipOutputStream : public RawOutputStream {
public:
    GZipOutputStream(const std::string &filename);

    GZipOutputStream(int fd);
//    GZipOutputStream(const std::string &);
    GZipOutputStream(const Util::MaybePointer<RawOutputStream> &);
    ~GZipOutputStream();

    int fd();

    ssize_t write(const void *bytes, size_t size);
    off_t seek(off_t offset, int whence);
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

#endif // GZIPOUTPUTSTREAM_HPP
