#include "Polygon.h"

/*!
 *  \brief This module is a null constructor.
 */
Polygon::Polygon()
{}

/*!
 *  \brief This is a constructor function.
 *  \param vertices a reference to a vector<Point<double>>
 */
Polygon::Polygon(vector<Point<double>> &vertices) : vertices(vertices)
{
  if (vertices.size() == 0) {
    cout << "No vertices to construct the ploygon ...";
    exit(1);
  }
  for (int i=0; i<vertices.size()-1; i++) {
    Line<Point<double>> line(vertices[i],vertices[i+1]);
    sides.push_back(line);
  }
}

/*!
 *  \brief This is a constructor function.
 *  \param sides a reference to a vector<Line<Point<double>>>
 */
Polygon::Polygon(vector<Line<Point<double>>> &sides) : sides(sides)
{
  if (sides.size() == 0) {
    cout << "No sides to construct the ploygon ...";
    exit(1);
  }
  vertices.push_back(sides[0].startPoint());
  for (int i=0; i<sides.size(); i++) {
    vertices.push_back(sides[i].endPoint());
  }
}

/*!
 *  \brief This module is used to create a copy of a Polygon object
 *  \param source a reference to a Polygon
 */
Polygon::Polygon(const Polygon &source) : vertices(source.vertices), 
                                          sides(source.sides) 
{}

/*!
 *  \brief This module assigns a source polygon to a target polygon.
 *  \param source a reference to a Polygon
 *  \return a Polygon
 */
Polygon Polygon::operator=(const Polygon &source)
{
  if (this != &source) {
    vertices = source.vertices;
    sides = source.sides;
  }
  return *this;
}

/*!
 *  \brief This method is used to return the number of vertices of the polygon
 *  \return the number of vertices
 */
int Polygon::getNumberOfVertices()
{
  return vertices.size();
}

/*!
 *  \brief This method is used to return the number of sides of the polygon
 *  \return the number of sides
 */
int Polygon::getNumberOfSides()
{
  return sides.size();
}

/*!
 *  \brief This method computes the length of the polygon
 *  \return the length of all sides
 */
double Polygon::length()
{
  double sum = 0;
  for (int i=0; i<sides.size(); i++) {
    sum += lcb::geometry::length<double>(sides[i]);
  }
  return sum;
}

/*!
 *  \brief This method is used to sample points on the polygon.
 *  \param num_samples an integer
 *  \return a list of random points
 */
vector<Point<double>> Polygon::generateRandomPoints(int num_points)
{
  srand(time(NULL));
  vector<Point<double>> samples;
  for (int i=0; i<num_points; i++) {
    // randomly choose a side of the polygon
    int index = rand() % sides.size();

    // randomly choose the parameter value \in [0,1]
    double t = rand() / (double) RAND_MAX;
    Point<double> point_on_line = sides[index].getPoint(t);

    samples.push_back(point_on_line);
  }
  return samples;
}

/*!
 *  \brief This function computes the distance histogram function for 
 *  the polygon.
 *  \param num_samples an integer
 *  \param r a double
 *  \return the histogram function value
 */
double Polygon::computeDistanceHistogram(int num_samples, double r)
{
  vector<Point<double>> samples = generateRandomPoints(num_samples);
  //DistanceHistogram histogram(samples);
  //histogram.computeGlobalHistogram(r);
}

/*!
 *  \brief This method plots the polygon.
 */
void Polygon::draw()
{

}

