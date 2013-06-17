#include "DistanceHistogram.h"

/*!
 *  \brief This is a null constructor module.
 */
DistanceHistogram::DistanceHistogram()
{}

/*!
 *  \brief This is a constructor module.
 *  \param polygon a reference to a Polygon
 */
DistanceHistogram::DistanceHistogram(Polygon &polygon) : polygon(polygon)
{}

/*!
 *  \brief This module is used to create a copy of a DistanceHistogram object
 *  \param source a reference to a DistanceHistogram
 */
DistanceHistogram::DistanceHistogram(const DistanceHistogram &source) :
                   polygon(source.polygon), point_set(source.point_set)
{}

/*!
 *  \brief This module assigns a source histogram to a target histogram.
 *  \param source a reference to a DistanceHistogram
 *  \return a DistanceHistogram
 */
DistanceHistogram DistanceHistogram::operator=(const DistanceHistogram &source)
{
  if (this != &source) {
    polygon = source.polygon;
    point_set = source.point_set;
  }
  return *this;
}

/*!
 *  \brief This function is used to construct the finite point set
 *  to evaluate the distance histogram function
 *  \param num_points an integer
 */
void DistanceHistogram::constructSamples(int num_points)
{
  point_set = polygon.generateRandomPoints(num_points);
}

/*!
 *  \brief This function is used to construct the finite point set
 *  to evaluate the distance histogram function
 */
void DistanceHistogram::constructSamples()
{
  int num_points = polygon.length() * POINTS_PER_UNIT;
  constructSamples(num_points);
}

/*!
 *  \brief This function returns the random points generated on the polygon.
 *  \return the generated samples 
 */
vector<Point<double>> DistanceHistogram::getSamples()
{
  return point_set;
}

/*!
 *  \brief This function counts the number of points that lie within a circle
 *  of a given radius.
 *  \param centre a reference to a Point<double>
 *  \param r a double
 *  \param number of internal points
 */
int DistanceHistogram::computeNumberOfInternalPoints(Point<double> &centre,
                                                     double r)
{
  int count = 0;
  for (int i=0; i<point_set.size(); i++) {
    double distance = lcb::geometry::distance<double>(centre,point_set[i]);
    if (distance <= r) {
      count++;
    }
  }
  return count;
}

/*!
 *  \brief This function is used to calculate the local histogram function
 *  value for a given value of r.
 *  \param r a double
 *  \return the local histogram function values
 */
vector<double> DistanceHistogram::computeLocalHistogram(double r)
{
  vector<double> local_histogram(point_set.size());
  for (int i=0; i<point_set.size(); i++) {
    int num_internal_points = computeNumberOfInternalPoints(point_set[i],r);
    local_histogram[i] = num_internal_points / (double) point_set.size();
  }
  return local_histogram;
}

/*!
 *  \brief This function computes the global histogram value
 *  \param r a double
 *  \return the global histogram function value
 */
double DistanceHistogram::computeGlobalHistogram(double r)
{
  double global_histogram = 0;
  vector<double> local_histogram = computeLocalHistogram(r);
  for (int i=0; i<point_set.size(); i++) {
    global_histogram += local_histogram[i];
  }
  return global_histogram / point_set.size();
}

/*!
 *  \brief This function computes the global histogram values for different
 *  values of r
 *  \param num_points an integer
 *  \return the list of distance histogram values
 */
pair<vector<double>,vector<double>> 
DistanceHistogram::computeGlobalHistogramValues(int num_points)
{
  double dr = 0.05;
  double length = polygon.length();
  vector<double> r_values;
  double r = dr;
  while (1) {
    if (r > length) {
      break;
    }
    r_values.push_back(r);
    r += dr;
  }
  return computeGlobalHistogramValues(r_values,num_points);
}

/*!
 *  \brief This function computes the global histogram values for different
 *  values of r in the provided list
 *  \param r a reference to a vector<double>
 *  \param num_points an integer
 *  \return the list of distance histogram values
 */
pair<vector<double>,vector<double>> 
DistanceHistogram::computeGlobalHistogramValues(vector<double> &r, int num_points)
{
  if (num_points == 0) {
    constructSamples();
  } else {
    constructSamples(num_points);
  }
  vector<double> values(r.size(),0);
  for (int i=0; i<r.size(); i++) {
    values[i] = computeGlobalHistogram(r[i]);
  }
  pair<vector<double>,vector<double>> results;
  results.first = r;
  results.second = values;
  return results;
}

