#ifndef CURVE_H
#define CURVE_H

#include "Header.h"

class Curve
{
  public:
    //! Null constructor
    Curve();

    //! Constructor
    Curve(vector<Point<double>> &);

    //! Assignment operator
    virtual Curve operator=(const Curve &); 

    //! Length of the curve
    virtual double length();

    //! Generate random points on the curve
    virtual vector<Point<double>> generateRandomPoints(int) {}

  protected:
    //! Points on the curve
    vector<Point<double>> points;
};

#endif

