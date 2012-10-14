
#ifndef DEFLATEINPUTSTREAM_HPP
#define DEFLATEINPUTSTREAM_HPP

#include <string>
#include <zlib.h>

#include "RawInputStream.hpp"
#include "Buffer.hpp"
#include <Util/MaybePointer.hpp>

#ifndef ZLIB_H
typedef struct gzFile_s *gzFile;
#endif

namespace IOStream {

class DeflateInputStream : public RawInputStream {
public:
    DeflateInputStream(const std::string &);
    DeflateInputStream(int fd);

    DeflateInputStream(const Util::MaybePointer<RawInputStream> &raw);
    ~DeflateInputStream();

    int fd();
    
    ssize_t read(void *bytes, size_t size);
    ssize_t peek(void *bytes, size_t size);
    off_t seek(off_t offset, int whence);
    void putBack();
    void finish();
    void close();
private:
    void init();
    void populateBuffer();

    z_stream zstream;
    Buffer buffer;
    Util::MaybePointer<RawInputStream> raw;
};

}

#endif // DEFLATEOUTPUTSTREAM_HPP
