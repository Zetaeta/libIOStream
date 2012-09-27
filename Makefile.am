#SUBDIRS = src

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libIOStream.la

libIOStream_la_CXXFLAGS = -fPIC

libIOStream_la_LDFLAGS = -lendian

libIOStream_la_includedir = $(includedir)/IOStream

libIOStream_la_SOURCES = src/InputStream.cpp src/OutputStream.cpp src/GZipInputStream.cpp src/GZipOutputStream.cpp src/PlainInputStream.cpp src/PlainOutputStream.cpp src/Buffer.cpp src/DeflateInputStream.cpp src/DeflateOutputStream.cpp

libIOStream_la_include_HEADERS = src/Endian.hpp src/InputStream.hpp src/OutputStream.hpp src/GZipInputStream.hpp src/GZipOutputStream.hpp src/PlainInputStream.hpp src/PlainOutputStream.hpp src/Buffer.hpp src/DeflateInputStream.hpp src/DeflateOutputStream.hpp
