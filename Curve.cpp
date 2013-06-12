#include "Curve.h"

/*!
 *  \brief This is a null constructor module.
 */
Curve::Curve()
{}

/*!
 *  \brief This is a constructor module
 *  \param points a reference to a vector<Point<double>>
 */
Curve::Curve(vector<Point<double>> &points) : points(points)
{}

/*!
 *  \brief This is an assignment operator
 *  \param source a reference to a Curve
 *  \return the source curve assigned to a target curve
 */
Curve Curve::operator=(const Curve &source) 
{
  points = source.points;
}

/*!
 *  \brief This function computes the length of the curve as sum of the
 *  distances between successive points.
 *  \return the curve length
 */
double Curve::length()
{
  double sum = 0;
  for (int i=0; i<points.size()-1; i++) {
    sum += lcb::geometry::distance<double>(points[i],points[i+1]);
  }
  return sum;
}

