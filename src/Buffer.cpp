
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <string.h>

#include "Buffer.hpp"

using std::underflow_error;
using std::overflow_error;
using std::min;
using std::ostringstream;

namespace IOStream {

Buffer::Buffer(int length)
:startPos(0), endPos(0), fullSize_(length) {
    buf = new uint8_t[length];
}

uint8_t Buffer::take() {
    if ((endPos - startPos) < 1) {
        throw underflow_error("Buffer is empty!");
    }
    return buf[startPos++];
}

void Buffer::take(uint8_t *output, size_t len) {
    if ((endPos - startPos) < len) {
        ostringstream ss;
        ss << "Not enough bytes in buffer: contains " << (endPos - startPos) << ", " << len << " required";
        throw underflow_error(ss.str());
    }
    memcpy(output, buf, len);
    startPos += len;
}

size_t Buffer::request(uint8_t *output, size_t len) {
    size_t taken = min(len, (endPos - startPos));
    memcpy(output, buf, taken);
    startPos += taken;
}

uint8_t * Buffer::take(size_t len) {
    if ((endPos - startPos) < len) {
        ostringstream ss;
        ss << "Not enough bytes in buffer: contains " << (endPos - startPos) << ", " << len << " taken";
        throw underflow_error(ss.str());
    }
    uint8_t *cur = &buf[startPos];
    startPos += len;
    return cur;
}

void Buffer::add(uint8_t *bytes, size_t len) {
    if ((fullSize_  - endPos) < len) {
        ostringstream ss;
        ss << "Cannot add bytes: space available: " << (fullSize_ - endPos) << ", " << len << " required.";
        throw overflow_error(ss.str());
    }
    memcpy(&buf[endPos], bytes, len);
    endPos += len;
}

size_t Buffer::offer(uint8_t *bytes, size_t len) {
    size_t taken = min(len, fullSize_ - endPos);
    memcpy(&buf[endPos], bytes, taken);
    endPos += taken;
    return taken;
}

void Buffer::add(size_t len) {
    if ((fullSize_ - endPos) < len) {
        ostringstream ss;
        ss << "Cannot add bytes: space available: " << (fullSize_ - endPos) << ", " << len << " required.";
        throw overflow_error(ss.str());
    }
    endPos += len;
}

Buffer::iterator Buffer::begin() {
    return &buf[startPos];
}

Buffer::iterator Buffer::end() {
    return &buf[endPos];
}

Buffer::iterator Buffer::trueBegin() {
    return buf;
}

Buffer::iterator Buffer::trueEnd() {
    return &buf[fullSize_];
}

size_t Buffer::availableBytes() {
    return endPos - startPos;
}

size_t Buffer::available() {
    return endPos - startPos;
}

size_t Buffer::spaceAfter() {
    return fullSize_ - endPos;
}

size_t Buffer::spaceBefore() {
    return startPos;
}

size_t Buffer::totalSpace() {
    return fullSize_ - (endPos - startPos);
}

void Buffer::shiftToStart() {
    if (startPos == 0) { // Buffer is already at start.
        return;
    }
    if (startPos == endPos) { // Buffer is empty.
        startPos = 0;
        endPos = 1;
    }
    memmove(buf, &buf[startPos], endPos - startPos);
    endPos -= startPos;
    startPos = 0;
}

size_t Buffer::fullSize() {
    return fullSize_;
}

uint8_t Buffer::operator[](size_t index) {
    return buf[startPos + index];
}

}

