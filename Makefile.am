#SUBDIRS = src

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libIOStream.la

libIOStream_la_CXXFLAGS = -fPIC -Wall

libIOStream_la_LDFLAGS = -lendian

libIOStream_la_includedir = $(includedir)/IOStream

libIOStream_la_SOURCES = src/Buffer.cpp src/ErrorHandler.hpp \
    src/InputStream.cpp src/OutputStream.cpp \
    src/RawInputStream.cpp src/RawOutputStream.cpp \
    src/FileInputStream.cpp src/FileOutputStream.cpp \
    src/GZipInputStream.cpp src/GZipOutputStream.cpp \
    src/PlainInputStream.cpp src/PlainOutputStream.cpp \
    src/DeflateInputStream.cpp src/DeflateOutputStream.cpp

libIOStream_la_include_HEADERS = src/Buffer.hpp src/Endian.hpp src/ErrorHandler.hpp \
    src/MaybePointer.hpp src/EmptyBuffer.hpp src/IOException.hpp \
    src/IOError.hpp src/InvalidIOOperation.hpp src/InvalidFileDescriptor.hpp \
    src/InputStream.hpp src/OutputStream.hpp \
    src/RawInputStream.hpp src/RawOutputStream.hpp \
    src/FileInputStream.hpp src/RawOutputStream.hpp \
    src/GZipInputStream.hpp src/GZipOutputStream.hpp \
    src/PlainInputStream.hpp src/PlainOutputStream.hpp \
    src/DeflateInputStream.hpp src/DeflateOutputStream.hpp
