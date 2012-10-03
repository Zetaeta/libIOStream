
#ifndef PLAINOUTPUTSTREAM_HPP
#define PLAINOUTPUTSTREAM_HPP

#include <string>

#include <sys/types.h>

#include "RawOutputStream.hpp"
#include "Endian.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class PlainOutputStream : public RawOutputStream {
public:
    PlainOutputStream(const std::string &);
    PlainOutputStream(int fd);
    ~PlainOutputStream();

    int fd();

    ssize_t write(const void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    FILE *file;
};

}

#endif // PLAINOUTPUTSTREAM_HPP
