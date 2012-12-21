
#ifndef FILEIOSTREAM_HPP
#define FILEIOSTREAM_HPP

#include "RawInputOutputStream.hpp"

namespace IOStream {

class FileIOStream : public RawInputOutputStream {
public:
    FileIOStream(const std::string &file);
    FileIOStream(int fd);
    off_t seek(off_t offset, int whence);
    void close();
    inline int fd() const {
        return fd_;
    }
    ssize_t read(void *, size_t length);
    ssize_t peek(void *, size_t length);
    ssize_t write(const void *, size_t length);
private:
    int fd_;
};

}

#endif
