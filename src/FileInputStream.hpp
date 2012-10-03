
#ifndef FILEINPUTSTREAM_HPP
#define FILEINPUTSTREAM_HPP

#include "RawInputStream.hpp"

namespace IOStream {

class FileInputStream : public RawInputStream {
public:
    FileInputStream(const std::string &);
    FileInputStream(int fd);

    ssize_t read(void *, size_t length);
    ssize_t peek(void *, size_t length);
    void seek(size_t offset, int whence);
    void close();
private:
    int fd_;
};

}

#endif
