#pragma once
#include "MathUtil.h"

class Interval {
 public:
  float start;
  float end;

  Interval(float start = 0, float end = Constants::FLOAT_INF) : start(start), end(end) {}

  bool inRangeInclusive(float val) const { return (val > start && val < end); }

  bool inRangeExclusive(float val) const { return (val >= start && val <= end); }
};

namespace Intervals {
inline const Interval inf(-Constants::FLOAT_INF, Constants::FLOAT_INF);
}
