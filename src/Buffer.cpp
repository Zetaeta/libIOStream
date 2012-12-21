
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <string.h>

#include "Buffer.hpp"

using std::underflow_error;
using std::overflow_error;
using std::min;
using std::max;
using std::ostringstream;

namespace IOStream {

Buffer::Buffer(size_t length, bool autoResize)
:startPos(0), endPos(0), fullSize_(length), autoResize(autoResize) {
    buf = new uint8_t[length];
}

uint8_t Buffer::take() {
    if (ssize_t(endPos - startPos) < 1) {
        throw underflow_error("Buffer is empty!");
    }
    return buf[startPos++];
}

void Buffer::take(void *output, size_t len) {
    if (ssize_t(endPos - startPos) < ssize_t(len)) {
        ostringstream ss;
        ss << "Not enough bytes in buffer: contains " << (endPos - startPos) << ", " << len << " required";
        throw underflow_error(ss.str());
    }
    memcpy(output, begin(), len);
    startPos += len;
}

size_t Buffer::request(void *output, size_t len) {
    size_t taken = min(len, available());
    memcpy(output, begin(), taken);
    startPos += taken;
    return taken;
}

uint8_t * Buffer::take(size_t len) {
    if (ssize_t(endPos - startPos) < ssize_t(len)) {
        ostringstream ss;
        ss << "Not enough bytes in buffer: contains " << (endPos - startPos) << ", " << len << " taken";
        throw underflow_error(ss.str());
    }
    uint8_t *cur = &buf[startPos];
    startPos += len;
    return cur;
}

void Buffer::addByte(uint8_t b) {
    if (ssize_t(fullSize_ - endPos) < 1) {
        if (autoResize) {
            if (fullSize_ - (endPos - startPos) >= 1) {
                shiftToStart();
            }
            else {
                size_t newSize = fullSize_ + max(size_t(1), fullSize_ > 128 ? fullSize_ / 2 : fullSize_);
                resize(newSize);
            }
        }
        else {
            throw overflow_error("Cannot add byte: buffer is full");
        }
    }
//    cout << "Buffer::addByte(): fullSize_ = " << fullSize_ << ", endPos = " << endPos << '\n';
    buf[endPos++] = b;
}

void Buffer::add(const void *bytes, size_t len) {
    if (ssize_t(fullSize_ - endPos) < ssize_t(len)) {
        if (autoResize) {
            if (fullSize_ - (endPos - startPos) >= len) {
                shiftToStart();
            }
            else {
                resize(fullSize_ + max(len, fullSize_ > 128 ? fullSize_ / 2 : fullSize_));
            }
        }
        else {
            ostringstream ss;
            ss << "Cannot add bytes: space available: " << (fullSize_ - endPos) << ", " << len << " required.";
            throw overflow_error(ss.str());
        }
    }
    memcpy(&buf[endPos], bytes, len);
    endPos += len;
}

size_t Buffer::offer(const void *bytes, size_t len) {
    size_t taken = min(len, fullSize_ - endPos);
    memcpy(&buf[endPos], bytes, taken);
    endPos += taken;
    return taken;
}

void Buffer::add(size_t len) {
    if (ssize_t(fullSize_ - endPos) < ssize_t(len)) {
        if (autoResize) {
            if (fullSize_ - (endPos - startPos) >= len) {
                shiftToStart();
            }
            else {
                resize(fullSize_ + max(len, fullSize_ > 128 ? fullSize_ / 2 : fullSize_));
            }
        }
        else {
            ostringstream ss;
            ss << "Cannot add bytes: space available: " << (fullSize_ - endPos) << ", " << len << " required.";
            throw overflow_error(ss.str());
        }
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

Buffer::const_iterator Buffer::begin() const {
    return &buf[startPos];
}

Buffer::const_iterator Buffer::end() const {
    return &buf[endPos];
}

Buffer::const_iterator Buffer::trueBegin() const {
    return buf;
}

Buffer::const_iterator Buffer::trueEnd() const {
    return &buf[fullSize_];
}


size_t Buffer::availableBytes() const {
    return endPos - startPos;
}

size_t Buffer::available() const {
    return endPos - startPos;
}

size_t Buffer::spaceAfter() const {
    return fullSize_ - endPos;
}

size_t Buffer::spaceBefore() const {
    return startPos;
}

size_t Buffer::totalSpace() const {
    return fullSize_ - (endPos - startPos);
}

void Buffer::shiftToStart() {
    if (startPos == 0) { // Buffer is already at start.
        return;
    }
    if (startPos == endPos) { // Buffer is empty.
        startPos = 0;
        endPos = 0;
    }
    memmove(buf, &buf[startPos], endPos - startPos);
    endPos -= startPos;
    startPos = 0;
}

size_t Buffer::fullSize() const {
    return fullSize_;
}

uint8_t Buffer::operator[](size_t index) const {
    return buf[startPos + index];
}

void Buffer::resize(size_t length) {
    uint8_t *newBuf = new uint8_t[length];
    memcpy(newBuf, &buf[startPos], min(endPos - startPos, length));
    delete[] buf;
    buf = newBuf;
    endPos -= startPos;
    startPos = 0;
    fullSize_ = length;
}

off_t Buffer::seek(off_t length, int whence) {
    switch (whence) {
    case SEEK_SET:
        startPos = length;
        break;
    case SEEK_CUR:
        startPos += length;
        break;
    case SEEK_END:
        startPos = endPos - length;
        break;
    }
    return startPos;
}

}

