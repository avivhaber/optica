#include "Intersection.h"

Intersection::Intersection(bool hit, const Object* obj, float t, Point point)
: hit(hit), obj(obj), t(t), point(point) {}
