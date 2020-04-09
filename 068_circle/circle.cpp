#include"circle.h"
#include<math.h>
void Circle::move(double dx, double dy){
  points.move(dx,dy);
}
double cos(double a, double b, double c){
  double cos=(a*a+b*b-c*c)/(2*a*b);
  return cos;
}
double Circle::intersectionArea(const Circle & otherCircle){

  double dis=points.distanceFrom(otherCircle.points);
  double r1=this->radius;
  double r2=otherCircle.radius;
  if((r1+r2)<=dis){
    return 0;
  }
  if((r1-r2)>=dis){
    return r2*r2*acos(-1);
  }
  if((r2-r1)>dis){
    return r1*r1*acos(-1);
  }
  else{
    double angle1=acos(cos(r1,dis,r2));
    double angle2=acos(cos(r2,dis,r1));
    double area=r1*r1*angle1+r2*r2*angle2-r1*dis*sin(angle1);
    return area;
  }
}
