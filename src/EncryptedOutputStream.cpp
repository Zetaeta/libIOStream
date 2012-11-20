
#include <sstream>
#include <bitset>

#include <unistd.h>

#include <openssl/evp.h>

#include <Util/ErrorHandler.hpp>

#include "EncryptedOutputStream.hpp"

namespace IOStream {

EncryptedOutputStream::EncryptedOutputStream(int socketfd, EVP_CIPHER_CTX *encryptor)
:socketfd(socketfd), encryptor(encryptor) {

}

ssize_t EncryptedOutputStream::write(const void *buf, size_t length) {
    int outLength = length + encryptor->cipher->block_size - 1;
    uint8_t *output = new uint8_t[outLength];
    EVP_EncryptUpdate(encryptor, output, &outLength, static_cast<const uint8_t *>(buf), length);
    ssize_t written = ::write(socketfd, output, outLength);
    if (written < 0) {
        throwException(errno);
    }
    delete[] output;
    return written;
}

off_t EncryptedOutputStream::seek(off_t length, int whence) {
    return 0;
}

void EncryptedOutputStream::close() {
    ::close(socketfd);
}

}

