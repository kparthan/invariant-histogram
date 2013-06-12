#ifndef DISTANCE_HISTOGRAM_H
#define DISTANCE_HISTOGRAM_H

#include "Header.h"
#include "Polygon.h"

class DistanceHistogram
{
  private:
    //! the curve that is abstracted
    Curve *curve;

    //! list of points
    vector<Point<double>> point_set;

    //! Sample points on the curve
    void constructSamples(int);
 
    //! Compute number of internal points
    int computeNumberOfPointsWithinCircle(Point<double> &, double);

  public:
    //! Null constructor
    DistanceHistogram();

    //! Constructor
    DistanceHistogram(Curve *);

    //! Copy constructor
    DistanceHistogram(const DistanceHistogram &);

    //! Assignment operator
    DistanceHistogram operator=(const DistanceHistogram &);

    //! Compute the local histogram function
    vector<double> computeLocalHistogram(int, double);

    //! Compute the global histogram function
    double computeGlobalHistogram(double);

    //! Compute the global histogram values for several values of r
    vector<double> computeGlobalHistogramValues();

    //! Compute the global histogram values for given values of r
    vector<double> computeGlobalHistogramValues(vector<double> &);
};

#endif

