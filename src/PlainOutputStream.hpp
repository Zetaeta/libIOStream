
#ifndef PLAINOUTPUTSTREAM_HPP
#define PLAINOUTPUTSTREAM_HPP

#include <string>

#include <sys/types.h>

#include "OutputStream.hpp"
#include "Endian.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class PlainOutputStream : public OutputStream {
public:
    PlainOutputStream(const std::string &, Endian = NATIVE);
    PlainOutputStream(int fd, Endian = NATIVE);
    ~PlainOutputStream();

    int fd();

    ssize_t write(const void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    FILE *file;
    bool closed;
};

}

#endif // PLAINOUTPUTSTREAM_HPP
