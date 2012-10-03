
#ifndef IOERROR_HPP
#define IOERROR_HPP

#include "IOException.hpp"

namespace IOStream {

class IOError : public IOException {
public:
    IOError(const std::string &what = "IOError")
    :IOException(what) {}
};

}

#endif

