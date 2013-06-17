#include "Support.h"
#include "Polygon.h"
#include "DistanceHistogram.h"

int main(int argc, char **argv)
{
  int num_points = parseCommandLineInput(argc,argv);
  pair<vector<double>,vector<double>> results1,results2,results3;

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
  DistanceHistogram hist1(square);
  results1 = hist1.computeGlobalHistogramValues(num_points);
  vector<Point<double>> samples = hist1.getSamples();
  square.draw("square",samples);
  square.save("square",results1);

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
  DistanceHistogram hist2(rhombus);
  results2 = hist2.computeGlobalHistogramValues(num_points);
  samples = hist2.getSamples();
  rhombus.draw("rhombus",samples);
  rhombus.save("rhombus",results2);

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
  DistanceHistogram hist3(rectangle);
  results3 = hist3.computeGlobalHistogramValues(num_points);
  samples = hist3.getSamples();
  rectangle.draw("rectangle",samples);
  rectangle.save("rectangle",results3);

  compareResults();
}

