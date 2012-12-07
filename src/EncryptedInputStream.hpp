
#ifndef ENCRYPTEDINPUTSTREAM_HPP
#define ENCRYPTEDINPUTSTREAM_HPP

#include <stdint.h>

#include <Util/stlfwd.hpp>

#include "RawInputStream.hpp"
#include "Buffer.hpp"

#ifndef CIPHER_BUFFER_LENGTH
#define CIPHER_BUFFER_LENGTH 1024
#endif

#ifndef HEADER_ENVELOPE_H
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;
#endif

namespace IOStream {

class EncryptedInputStream : public RawInputStream {
public:
    EncryptedInputStream(int socketfd, EVP_CIPHER_CTX *);
    EncryptedInputStream()
    :input(0), output(0) {}

    ssize_t read(void *buf, size_t count);
    ssize_t peek(void *buf, size_t count);
    off_t seek(off_t length, int whence);
    void close();
private:
    void populateInput();

    int socketfd;
    EVP_CIPHER_CTX *decryptor;
    Buffer input;
    Buffer output;
};

}

#endif
