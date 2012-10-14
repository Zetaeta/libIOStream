
#ifndef SOCKETSTREAM_HPP
#define SOCKETSTREAM_HPP

#include "SocketInputStream.hpp"
#include "SocketOutputStream.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "RawInputOutputStream.hpp"

namespace IOStream {

class SocketStream : public SocketInputStream, public SocketOutputStream {
public:
    SocketStream(int socketfd)
    :SocketInputStream(new FileInputStream(socketfd)), SocketOutputStream(new FileOutputStream(socketfd)) {}

    SocketStream(const Util::MaybePointer<RawInputStream> &in, const Util::MaybePointer<RawOutputStream> &out)
    :SocketInputStream(in), SocketOutputStream(out) {}

 //   SocketStream & operator=(SocketStream &&other) {
//        SocketInputStream::operator=(std::move(other));
//        SocketOutputStream::operator=(std::move(other));
//        return *this;
//    }

    SocketStream(const Util::MaybePointer<RawInputOutputStream> &raw)
    :SocketInputStream(raw), SocketOutputStream(raw) {}
};

}

#endif
