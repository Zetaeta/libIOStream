
#ifndef FILEOUTPUTSTREAM_HPP
#define FILEOUTPUTSTREAM_HPP

#include <string>

#include "RawOutputStream.hpp"

namespace IOStream {

class FileOutputStream : public RawOutputStream {
public:
    FileOutputStream(const std::string &);
    FileOutputStream(int fg);

    inline int fd() const {
        return fd_;
    }

    ssize_t write(const void *, size_t length);
    off_t seek(off_t offset, int whence);
    void close();
private:
    int fd_;
};

}

#endif
