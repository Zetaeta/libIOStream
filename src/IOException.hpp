
#ifndef IOEXCEPTION_HPP
#define IOEXCEPTION_HPP

#include <string>
#include <stdexcept>

namespace IOStream {

class IOException : public std::runtime_error {
public:
    IOException(const std::string &what)
    :std::runtime_error(what) {
    }
};

}

#endif
