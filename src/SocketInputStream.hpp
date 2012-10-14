
#ifndef SOCKETINPUTSTREAM_HPP
#define SOCKETINPUTSTREAM_HPP

#include "InputStream.hpp"

namespace IOStream {

class SocketInputStream : public InputStream {
public:
    SocketInputStream(const Util::MaybePointer<RawInputStream> &raw)
    :InputStream(raw) {}

    SocketInputStream(int fd);

    SocketInputStream & operator>>(std::string &);

    using InputStream::operator>>;
    using InputStream::operator=;
};

}

#endif
