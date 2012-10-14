
#ifndef ENCRYPTEDOUTPUTSTREAM_HPP
#define ENCRYPTEDOUTPUTSTREAM_HPP

#include <string>
#include <stdint.h>

#include "RawOutputStream.hpp"

#ifndef HEADER_ENVELOPE_H
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;
#endif

namespace IOStream {

class EncryptedOutputStream : public RawOutputStream {
public:
    EncryptedOutputStream(int socketfd, EVP_CIPHER_CTX *decryptor);
    EncryptedOutputStream() {}

    ssize_t write(const void *buf, size_t count);
    off_t seek(off_t length, int whence);
    void close();
private:
    int socketfd;
    EVP_CIPHER_CTX *encryptor;

};

}

#endif
