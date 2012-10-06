
#ifndef INVALIDIOOPERATION_HPP
#define INVALIDIOOPERATION_HPP

#include "IOException.hpp"

namespace IOStream {

class InvalidIOOperation : public IOException {
public:
    InvalidIOOperation(const std::string &what = "UnsupportedOperationException")
    :IOException(what) {}
};

}

#endif

