
#ifndef DEFLATEINPUTSTREAM_HPP
#define DEFLATEINPUTSTREAM_HPP

#include <string>
#include <zlib.h>

#include "InputStream.hpp"
#include "Buffer.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class DeflateInputStream : public InputStream {
public:
    DeflateInputStream(const std::string &, Endian = NATIVE);
    DeflateInputStream(int fd, Endian = NATIVE);
    ~DeflateInputStream();

    int fd();
    
    ssize_t read(void *bytes, size_t size);
    ssize_t peek(void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void putBack();
    void close();
private:
    void init();
    void populateBuffer();

    z_stream zstream;
    Buffer buffer;
    int fd_;
    bool closed;
};

}

#endif // DEFLATEOUTPUTSTREAM_HPP
