
#ifndef INPUTOUTPUTSTREAM_HPP
#define INPUTOUTPUTSTREAM_HPP

#include "InputStream.hpp"
#include "OutputStream.hpp"
#include "RawInputOutputStream.hpp"

namespace IOStream {

class InputOutputStream : public InputStream, public OutputStream {
public:
    InputOutputStream(const MaybePointer<RawInputStream> &in = NULL, const MaybePointer<RawOutputStream> &out = NULL)
    :InputStream(in), OutputStream(out) {
    }

    InputOutputStream(MaybePointer<RawInputOutputStream> raw)
    :InputStream(raw), OutputStream(raw) {}
};

}

#endif
