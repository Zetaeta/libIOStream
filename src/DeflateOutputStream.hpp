
#ifndef DEFLATEOUTPUTSTREAM_HPP
#define DEFLATEOUTPUTSTREAM_HPP

#include <string>
#include <zlib.h>

#include "OutputStream.hpp"
#include "Buffer.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class DeflateOutputStream : public OutputStream {
public:
    DeflateOutputStream(const std::string &, Endian = NATIVE);
    DeflateOutputStream(int fd, Endian = NATIVE);
    ~DeflateOutputStream();

    int fd();

    ssize_t write(const void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    void init();
    void writeBuffer();
    
    z_stream zstream;
    Buffer buffer;
    int fd_;
    bool closed;
};

}

#endif // DEFLATEOUTPUTSTREAM_HPP
