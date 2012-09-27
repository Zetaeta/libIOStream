
#ifndef INPUTOUTPUTSTREAM_HPP
#define INPUTOUTPUTSTREAM_HPP

namespace IOStream {

class InputOutputStream : public virtual InputStream, public virtual OutputStream {
public:
    virtual ~InputOutputStream() = 0;
};

}

#endif
