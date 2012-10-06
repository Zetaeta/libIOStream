
#include <errno.h>
#include <string.h>

#include "ErrorHandler.hpp"
#include "InvalidFileDescriptor.hpp"
#include "IOError.hpp"
#include "InvalidIOOperation.hpp"

using std::string;

namespace IOStream {

void throwException(int errorCode, const string &message) {
    switch (errorCode) {
    case EBADF:
        throw InvalidFileDescriptor(message != "" ? message : strerror(errorCode));
    case EINVAL:
        throw InvalidIOOperation(message != "" ? message : strerror(errorCode));
    case EISDIR:
        throw InvalidIOOperation(message != "" ? message : strerror(errorCode));
    case EIO:
        throw IOError(message != "" ? message : strerror(errorCode));
    default:
        throw IOException(message != "" ? message : strerror(errorCode));
    }
}

}
