
#ifndef PLAININPUTSTREAM_HPP
#define PLAININPUTSTREAM_HPP

#include <string>

#include <sys/types.h>

#include "RawInputStream.hpp"
#include "Endian.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class PlainInputStream : public RawInputStream {
public:
    PlainInputStream(const std::string &);
    PlainInputStream(int fd);
    ~PlainInputStream();

    int fd();
    
    ssize_t read(void *bytes, size_t size);
    ssize_t peek(void *bytes, size_t size);
    void seek(size_t offset, int whence);
    void close();
private:
    int fd_;
};

}

#endif // PLAINOUTPUTSTREAM_HPP
