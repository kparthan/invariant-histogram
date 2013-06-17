#ifndef DISTANCE_HISTOGRAM_H
#define DISTANCE_HISTOGRAM_H

#include "Header.h"
#include "Polygon.h"

class DistanceHistogram
{
  private:
    //! the curve that is abstracted
    Polygon polygon;

    //! list of points
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

    //!
    vector<Point<double>> getSamples();

    //! Compute the local histogram function
    vector<double> computeLocalHistogram(double);

    //! Compute the global histogram function
    double computeGlobalHistogram(double);

    //! Compute the global histogram values for several values of r
    pair<vector<double>,vector<double>> computeGlobalHistogramValues();

    //! Compute the global histogram values for given values of r
    pair<vector<double>,vector<double>> computeGlobalHistogramValues(vector<double> &);
};

#endif

