
#include <algorithm>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>

#include <openssl/evp.h>

#include "EncryptedInputStream.hpp"

using std::min;

namespace IOStream {

EncryptedInputStream::EncryptedInputStream(int socketfd, EVP_CIPHER_CTX *decryptor)
:socketfd(socketfd), decryptor(decryptor), input(CIPHER_BUFFER_LENGTH), output(CIPHER_BUFFER_LENGTH) {}

ssize_t EncryptedInputStream::read(void *buf, size_t count) {
    size_t added = 0;
    while (added < count) { // Buf is not full
        if (output.available() < (count - added)) {
            if (output.spaceBefore() > output.spaceAfter()) {
                output.shiftToStart();
            }
            if (input.available() == 0) { // Input buffer is empty.
                populateInput();
            }
            int outLen, inLen = min(input.available(), output.spaceAfter() - decryptor->cipher->block_size);
            EVP_DecryptUpdate(decryptor, output.end(), &outLen, input.begin(), inLen);
            input.take(inLen);
            output.add(outLen);
        }
        int copy = min(count - added, output.available());
//        memcpy(buf, output.begin(), copy);
        output.take(copy);
        output.take(buf, copy);
        added += copy;
    }
    return added;
}

void EncryptedInputStream::populateInput() {
    input.shiftToStart();
    ssize_t bytesRead = ::read(socketfd, input.end(), input.spaceAfter());
    if (bytesRead < 0) {
        return;
    }
    input.add(bytesRead);
}

ssize_t EncryptedInputStream::peek(void *out, size_t length) {
    return 0;
}

off_t EncryptedInputStream::seek(off_t length, int whence) {
    return 0;
}

void EncryptedInputStream::close() {
    ::close(socketfd);
}

}

