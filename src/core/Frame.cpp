#include "Frame.h"
#include <algorithm>

Frame::Frame(int width, int height) : width(width), height(height) {
  buffer = new Color*[width];
  for (int i = 0; i < width; i++) {
    buffer[i] = new Color[height];
  }
}

Frame::Frame(const Frame& other) : width(other.width), height(other.height) {
  buffer = new Color*[width];
  for (int i = 0; i < width; i++) {
    buffer[i] = new Color[height];
    std::copy(other.buffer[i], other.buffer[i] + height, buffer[i]);
  }
}

Frame& Frame::operator=(Frame other) {
  swap(*this, other);
  return *this;
}

Frame::~Frame() {
  for (int i = 0; i < width; i++) {
    delete[] buffer[i];
  }
  delete[] buffer;
}

void swap(Frame& first, Frame& second) {
  std::swap(first.width, second.width);
  std::swap(first.height, second.height);
  std::swap(first.buffer, second.buffer);
}
