#ifndef TRAB4_EDGE_H
#define TRAB4_EDGE_H

#include "point2d.h"

class edge {
 public:
  edge(const point<double>& point1, const point<double>& point2) : point1(point1), point2(point2) {}
  edge(const edge& other) : point1(other.point1), point2(other.point2) {}

  bool operator==(const edge& other) const {
    return (point1 == other.point1 && point2 == other.point2) ||
        (point1 == other.point2 && point2 == other.point1);
  }

  void invalidate() {
    bad = true;
  }

  bool is_bad() const {
    return bad;
  }

  point<double> get_point1() const {
    return point1;
  }

  point<double> get_point2() const {
    return point2;
  }

 private:
  point<double> point1;
  point<double> point2;
  bool bad = false;
};

#endif //TRAB4_EDGE_H
