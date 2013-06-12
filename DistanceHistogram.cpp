#include "DistanceHistogram.h"

/*!
 *  \brief This is a null constructor module.
 */
DistanceHistogram::DistanceHistogram()
{}

/*!
 *  \brief This is a constructor module.
 *  \param curve a pointer to a Curve 
 */
DistanceHistogram::DistanceHistogram(Curve *curve) : curve(curve)
{}

/*!
 *  \brief This module is used to create a copy of a DistanceHistogram object
 *  \param source a reference to a DistanceHistogram
 */
DistanceHistogram::DistanceHistogram(const DistanceHistogram &source) :
                   curve(source.curve), point_set(source.point_set)
{}

/*!
 *  \brief This module assigns a source histogram to a target histogram.
 *  \param source a reference to a DistanceHistogram
 *  \return a DistanceHistogram
 */
DistanceHistogram DistanceHistogram::operator=(const DistanceHistogram &source)
{
  if (this != &source) {
    curve = source.curve;
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
  point_set = curve->generateRandomPoints(num_points);
}

/*!
 *  \brief This function counts the number of point_set that lie within a circle
 *  of a given radius.
 *  \param centre a reference to a Point<double>
 *  \param r a double
 *  \param number of internal point_set
 */
int DistanceHistogram::computeNumberOfPointsWithinCircle(Point<double> &centre,
                                                         double r)
{
  int num_point_set = 0;
  for (int i=0; i<point_set.size(); i++) {
    double distance = lcb::geometry::distance<double>(centre,point_set[i]);
    if (distance <= r) {
      num_point_set++;
    }
  }
  return num_point_set;
}

/*!
 *  \brief This function is used to calculate the local histogram function
 *  value for a given value of r.
 *  \param index an integer
 *  \param r a double
 *  \return the local histogram function values
 */
vector<double> DistanceHistogram::computeLocalHistogram(int index, double r)
{
  vector<double> local_histogram(point_set.size());
  for (int i=0; i<point_set.size(); i++) {
    int num_point_set_within = computeNumberOfPointsWithinCircle(point_set[i],r);
    local_histogram[i] = num_point_set_within / (double) point_set.size();
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
  for (int i=0; i<point_set.size(); i++) {
    vector<double> local_histogram = computeLocalHistogram(i,r);
    for (int j=0; j<local_histogram.size(); j++) {
      global_histogram += local_histogram[j];
    }
  }
  return global_histogram / point_set.size();
}

/*!
 *  \brief This function computes the global histogram values for different
 *  values of r
 *  \return the list of distance histogram values
 */
vector<double> DistanceHistogram::computeGlobalHistogramValues()
{
  vector<double> values(NUM_ITERATIONS,0);
  double length = curve->length();
  int delta_r = length / NUM_ITERATIONS;
  double r = delta_r;
  for (int i=0; i<NUM_ITERATIONS; i++) {
    values[i] = computeGlobalHistogram(r);
    r += delta_r;
  }
  return values;
}

/*!
 *  \brief This function computes the global histogram values for different
 *  values of r in the provided list
 *  \param r a reference to a vector<double>
 *  \return the list of distance histogram values
 */
vector<double> DistanceHistogram::computeGlobalHistogramValues(vector<double> &r)
{
  vector<double> values(r.size(),0);
  for (int i=0; i<r.size(); i++) {
    values[i] = computeGlobalHistogram(r[i]);
  }
  return values;
}

