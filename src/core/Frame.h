#pragma once

#include "Color.h"

class Frame {
 public:
  int width;
  int height;
  Color** buffer;

  Frame(int width = 1, int height = 1);
  Frame(const Frame& other);
  Frame& operator=(Frame other);
  ~Frame();
  friend void swap(Frame& first, Frame& second);
};
