
#ifndef INPUTOUTPUTSTREAM_HPP
#define INPUTOUTPUTSTREAM_HPP

#include "InputStream.hpp"
#include "OutputStream.hpp"
#include "RawInputOutputStream.hpp"

namespace IOStream {

class InputOutputStream : public InputStream, public OutputStream {
public:
    using InputStream::seek;
    using InputStream::close;

    InputOutputStream(const Util::MaybePointer<RawInputStream> &in, const Util::MaybePointer<RawOutputStream> &out)
    :InputStream(in), OutputStream(out) {
    }

    InputOutputStream(const Util::MaybePointer<RawInputOutputStream> &raw)
    :InputStream(raw), OutputStream(Util::MaybePointer<RawInputOutputStream>(*raw)) {} // OutputStream can't hold the same MaybePointer or it will try delete it aswell,
                                             // it has to be passed as a reference.

    virtual ~InputOutputStream() {}
};

}

#endif
