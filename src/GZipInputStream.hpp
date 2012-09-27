
#ifndef GZIPINPUTSTREAM_HPP
#define GZIPINPUTSTREAM_HPP

#include <string>

#include "InputStream.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class GZipInputStream : public InputStream {
public:
    GZipInputStream(const std::string &, Endian = NATIVE);
    GZipInputStream(int fd, Endian = NATIVE);
    ~GZipInputStream();

    int fd();
    
    ssize_t read(void *bytes, size_t size);
    ssize_t peek(void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    gzFile file;
    int fd_;
    bool closed;
};

}

#endif // GZIPOUTPUTSTREAM_HPP
