
#ifndef GZIPOUTPUTSTREAM_HPP
#define GZIPOUTPUTSTREAM_HPP

#include <string>

#include "RawOutputStream.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class GZipOutputStream : public RawOutputStream {
public:
    GZipOutputStream(const std::string &);
    GZipOutputStream(int fd);
    ~GZipOutputStream();

    int fd();

    ssize_t write(const void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    gzFile file;
    int fd_;
};

}

#endif // GZIPOUTPUTSTREAM_HPP
