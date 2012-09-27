
#ifndef GZIPOUTPUTSTREAM_HPP
#define GZIPOUTPUTSTREAM_HPP

#include <string>

#include "OutputStream.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class GZipOutputStream : public OutputStream {
public:
    GZipOutputStream(const std::string &, Endian = NATIVE);
    GZipOutputStream(int fd, Endian = NATIVE);
    ~GZipOutputStream();

    int fd();

    ssize_t write(const void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    gzFile file;
    int fd_;
    bool closed;
};

}

#endif // GZIPOUTPUTSTREAM_HPP
