#ifndef DISTANCE_HISTOGRAM_H
#define DISTANCE_HISTOGRAM_H

#include "Header.h"
#include "Polygon.h"

class DistanceHistogram
{
  private:
    //! The polygon used 
    Polygon polygon;

    //! List of points
    vector<Point<double>> point_set;

    //! Sample points on the curve
    void constructSamples(int);
 
    //! Sample points on the curve
    void constructSamples();
 
    //! Compute number of internal points
    int computeNumberOfInternalPoints(Point<double> &, double);

  public:
    //! Null constructor
    DistanceHistogram();

    //! Constructor
    DistanceHistogram(Polygon &);

    //! Copy constructor
    DistanceHistogram(const DistanceHistogram &);

    //! Assignment operator
    DistanceHistogram operator=(const DistanceHistogram &);

    //! Gets the generated random samples
    vector<Point<double>> getSamples();

    //! Compute the local histogram function
    vector<double> computeLocalHistogram(double);

    //! Compute the global histogram function
    double computeGlobalHistogram(double);

    //! Compute the global histogram values for several values of r
    pair<vector<double>,vector<double>> 
    computeGlobalHistogramValues(int);

    //! Compute the global histogram values for given values of r
    pair<vector<double>,vector<double>> 
    omputeGlobalHistogramValues(vector<double> &, int);
};

#endif

