
#include <vector>

#include <Util/Unicode.hpp>

#include "SocketInputStream.hpp"
#include "RawInputStream.hpp"
#include "FileInputStream.hpp"

using std::vector;

using Util::MaybePointer;

namespace IOStream {

SocketInputStream::SocketInputStream(int fd)
:InputStream(new FileInputStream(fd)) {}

SocketInputStream & SocketInputStream::operator>>(std::string &data) {
    uint16_t length;
    InputStream::operator>>(length);
    vector<uint16_t> ucs2(length);
    raw->read(ucs2.data(), length * 2);
    if (swap) {
        for (auto it = ucs2.begin(); it != ucs2.end(); ++it) {
            uint16_t u = *it;
            *it = (u << 8) | (u >> 8);
        }
    }
    data = Util::ucs2ToUtf8(ucs2);
    return *this;
}

}
