#SUBDIRS = src

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libIOStream.la

libIOStream_la_CXXFLAGS = -g -fPIC -Wall -std=c++11 -O0 -Werror

libIOStream_la_LDFLAGS = -lZUtil -lcrypto

libIOStream_la_includedir = $(includedir)/IOStream

libIOStream_la_SOURCES = src/Buffer.cpp  \
    src/InputStream.cpp src/OutputStream.cpp \
    src/RawInputStream.cpp src/RawOutputStream.cpp \
    src/FileInputStream.cpp src/FileOutputStream.cpp \
    src/GZipInputStream.cpp src/GZipOutputStream.cpp \
    src/DeflateInputStream.cpp src/DeflateOutputStream.cpp \
    src/ArrayInputStream.cpp src/ArrayOutputStream.cpp \
    src/EncryptedInputStream.cpp src/EncryptedOutputStream.cpp \
    src/SocketInputStream.cpp src/SocketOutputStream.cpp

libIOStream_la_include_HEADERS = src/Buffer.hpp src/Endian.hpp \
    src/InputStream.hpp src/OutputStream.hpp \
    src/RawInputStream.hpp src/RawOutputStream.hpp \
    src/FileInputStream.hpp src/FileOutputStream.hpp \
    src/GZipInputStream.hpp src/GZipOutputStream.hpp \
    src/DeflateInputStream.hpp src/DeflateOutputStream.hpp \
    src/ArrayInputStream.hpp src/ArrayOutputStream.hpp \
    src/InputOutputStream.hpp src/RawInputOutputStream.hpp \
    src/EncryptedInputStream.hpp src/EncryptedOutputStream.hpp \
    src/SocketInputStream.hpp src/SocketOutputStream.hpp src/SocketStream.hpp

