
#ifndef FILEINPUTSTREAM_HPP
#define FILEINPUTSTREAM_HPP

#include "RawOutputStream.hpp"

namespace IOStream {

class FileOutputStream : public RawOutputStream {
public:
    FileOutputStream(const std::string &);
    FileOutputStream(int fg);

    ssize_t write(const void *, size_t length);
    void seek(size_t offset, int whence);
    void close();
private:
    int fd_;
};

}

#endif
