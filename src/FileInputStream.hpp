
#ifndef FILEINPUTSTREAM_HPP
#define FILEINPUTSTREAM_HPP

#include <string>

#include "RawInputStream.hpp"

namespace IOStream {

class FileInputStream : public RawInputStream {
public:
    FileInputStream(const std::string &);
    FileInputStream(int fd);

    inline int fd() const {
        return fd_;
    }

    ssize_t read(void *, size_t length);
    ssize_t peek(void *, size_t length);
    off_t seek(off_t offset, int whence);
    void close();
private:
    int fd_;
};

}

#endif
