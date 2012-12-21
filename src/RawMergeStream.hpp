
#ifndef RAWINPUTOUTPUTSTREAM_HPP
#define RAWINPUTOUTPUTSTREAM_HPP

#include <Util/MaybePointer.hpp>

#include "RawInputOutputStream.hpp"

namespace IOStream {

class RawInputOutputStream : public RawInputOutputStream {
public:
    RawInputOutputStream(const Util::MaybePointer<RawInputStream> &in, const Util::MaybePointer<RawOutputStream> &out)
    :in(in), out(out) {}

    ssize_t read(void *out, size_t length) {
        return in->read(out, length);
    }

    ssize_t peek(void *out, size_t length) {
        return in->read(out, length);
    }

    off_t seek(off_t offset, int whence) {
        off_t rIn = in->seek(offset, whence);
        off_t rOut = in->seek(offset, whence);
        return rIn == rOut ? rIn : (rIn > rOut ? rIn : rOut);
    }

    void close() {
        in->close();
        out->close();
    }

    ssize_t write(const void *in, size_t length) {
        return out->write(in, length);
    }
private:
    Util::MaybePointer<RawInputStream> in;
    Util::MaybePointer<RawOutputStream> out;
};

}

#endif
