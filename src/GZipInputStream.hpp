
#ifndef GZIPINPUTSTREAM_HPP
#define GZIPINPUTSTREAM_HPP

#include <string>
#include <zlib.h>

#include "RawInputStream.hpp"
#include "Buffer.hpp"
#include "MaybePointer.hpp"

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class GZipInputStream : public RawInputStream {
public:
    GZipInputStream(const std::string &filename);

    GZipInputStream(int fd);

    GZipInputStream(const MaybePointer<RawInputStream> &raw);

    ~GZipInputStream();

    int fd();
    
    ssize_t read(void *bytes, size_t size);
    ssize_t peek(void *bytes, size_t size);
    off_t seek(off_t offset, int whence);
    void putBack();
    void close();
private:
    void init();
    void populateBuffer();

    z_stream zstream;
    Buffer buffer;
    MaybePointer<RawInputStream> raw;
};

}

#endif // GZIPOUTPUTSTREAM_HPP
