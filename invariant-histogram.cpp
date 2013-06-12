#include "Polygon.h"
#include "DistanceHistogram.h"

int main(int argc, char **argv)
{
  Point<double> p1(0,0,0);
  Point<double> p2(1,0,0);
  Point<double> p3(1,1,0);
  Point<double> p4(0,1,0);
  vector<Point<double>> points;
  points.push_back(p1);
  points.push_back(p2);
  points.push_back(p3);
  points.push_back(p4);
  points.push_back(p1);
  Polygon square(points);
  points.clear();

  double sqrt_2 = sqrt(2);
  p1 = Point<double>(0,0,0);
  p2 = Point<double>(1/sqrt_2,1/sqrt_2,0);
  p3 = Point<double>(0,sqrt_2,0);
  p4 = Point<double>(-1/sqrt_2,1/sqrt_2,0);
  points.push_back(p1);
  points.push_back(p2);
  points.push_back(p3);
  points.push_back(p4);
  points.push_back(p1);
  Polygon rhombus(points);
  points.clear();

  p1 = Point<double>(0,0,0);
  p2 = Point<double>(3,0,0);
  p3 = Point<double>(3,1,0);
  p4 = Point<double>(0,1,0);
  points.push_back(p1);
  points.push_back(p2);
  points.push_back(p3);
  points.push_back(p4);
  points.push_back(p1);
  Polygon rectangle(points);
  points.clear();

  Curve *c1 = &square;
  DistanceHistogram h1(c1);
  h1.constructSamples(20);
  h1.computeGlobalHistogram();  

  Curve *c2 = &rhombus;
  Curve *c3 = *rectangle;

}

