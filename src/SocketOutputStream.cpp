
#include <vector>

#include <Util/Unicode.hpp>

#include "SocketOutputStream.hpp"
#include "FileOutputStream.hpp"

using std::vector;

using Util::MaybePointer;

namespace IOStream {

SocketOutputStream::SocketOutputStream(int fd)
:OutputStream(new FileOutputStream(fd)) {}

SocketOutputStream & SocketOutputStream::operator<<(const std::string &data) {
    vector<uint16_t> usc2 = Util::utf8ToUcs2(data);
    if (swap) {
        for (size_t i=0; i<usc2.size(); ++i) {
            uint16_t u = usc2[i];
            usc2[i] = (u << 8) | (u >> 8);
        }
    }
    OutputStream::operator<<(static_cast<uint16_t>(usc2.size()));
    write(usc2.data(), usc2.size() * sizeof(uint16_t));
    return *this;
}

}
