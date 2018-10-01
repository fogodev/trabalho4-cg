#ifndef TRAB4_TRIANGLE_H
#define TRAB4_TRIANGLE_H

#include "point2d.h"
#include "edge.h"

class triangle {
 public:
  triangle(const point<double>& point1, const point<double>& point2, const point<double>& point3) :
      point1(point1),
      point2(point2),
      point3(point3),
      edge1(point1, point2),
      edge2(point2, point3),
      edge3(point3, point1) {}

  bool contains_point(const point<double>& subject) const {
    return point1 == subject || point2 == subject || point3 == subject;
  }

  bool contains_in_circle(const point<double>& subject) const {
    const double ab = point1.norm_squared();
    const double cd = point2.norm_squared();
    const double ef = point3.norm_squared();

    const point<double> circle_center{
        ((ab * (point3.y - point2.y) + cd * (point1.y - point3.y) + ef * (point2.y - point1.y)) /
            (
                point1.x * (point3.y - point2.y) + point2.x * (point1.y - point3.y)
                    + point3.x * (point2.y - point1.y))) * 0.5,

        ((ab * (point3.x - point2.x) + cd * (point1.x - point3.x) + ef * (point2.x - point1.x)) /
            (
                point1.y * (point3.x - point2.x) + point2.y * (point1.x - point3.x)
                    + point3.y * (point2.x - point1.x))) * 0.5
    };

    const double circle_radius = point1.distance_squared(circle_center);
    const double distance = subject.distance_squared(circle_center);

    return distance <= circle_radius;
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

  point<double> get_point3() const {
    return point3;
  }

  edge get_edge1() const {
    return edge1;
  }

  edge get_edge2() const {
    return edge2;
  }

  edge get_edge3() const {
    return edge3;
  }

 private:
  point<double> point1;
  point<double> point2;
  point<double> point3;
  edge edge1;
  edge edge2;
  edge edge3;
  bool bad = false;
};

#endif //TRAB4_TRIANGLE_H
