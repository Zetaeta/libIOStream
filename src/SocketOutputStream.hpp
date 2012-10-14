
#ifndef SOCKETOUTPUTSTREAM_HPP
#define SOCKETOUTPUTSTREAM_HPP

#include "OutputStream.hpp"

namespace IOStream {

class SocketOutputStream : public OutputStream {
public:
    SocketOutputStream(const Util::MaybePointer<RawOutputStream> &raw)
    :OutputStream(raw) {}

    SocketOutputStream(int fd);

    SocketOutputStream & operator<<(const std::string &data);

    using OutputStream::operator<<;
    using OutputStream::operator=;
};

}

#endif
