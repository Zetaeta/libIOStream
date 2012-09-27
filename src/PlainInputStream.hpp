
#ifndef PLAININPUTSTREAM_HPP
#define PLAININPUTSTREAM_HPP

#include <string>

#include <sys/types.h>

#include "InputStream.hpp"
#include "Endian.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class PlainInputStream : public InputStream {
public:
    PlainInputStream(const std::string &, Endian = NATIVE);
    PlainInputStream(int fd, Endian = NATIVE);
    ~PlainInputStream();

    int fd();
    
    ssize_t read(void *bytes, size_t size);
    ssize_t peek(void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    FILE *file;
    bool closed;
};

}

#endif // PLAINOUTPUTSTREAM_HPP
