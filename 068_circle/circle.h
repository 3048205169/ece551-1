#include "point.h"

class Circle{
 private:
  Point points;
  double const radius;

 public:
 Circle(Point points,double const radius):points(points),radius(radius){}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
