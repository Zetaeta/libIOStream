
#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include <string>

namespace IOStream {

void throwException(int errorCode, const std::string & = "");

}

#endif

