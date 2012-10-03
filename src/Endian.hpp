
#ifndef ENDIANENUM_HPP
#define ENDIANENUM_HPP

namespace IOStream {

enum Endian {
    // Big endian
    BIG,
    // Little endian
    LITTLE,
    // Platform native endian
    NATIVE
};

#ifndef DEFAULT_ENDIAN
#define DEFAULT_ENDIAN BIG
#endif

}

#endif
