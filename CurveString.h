#ifndef CURVE_STRING_H
#define CURVE_STRING_H

#include "Header.h"

class CurveString
{
  private:
    //! Vertices of the segments of the curves 
    vector<Point<double>> vertices;

    //! Sample points on the curve string
    vector<Point<double>> samples;

    //! Set of curves
    vector<Curve<double>*> curves;

    //! Lengths of the curves
    vector<double> lengths;

    //! Select a curve
    int getCurveIndex(double, vector<double> &);

  public:
    //! Null constructor
    CurveString();

    //! Constructor
    CurveString(vector<Point<double>> &);

    //! Constructor
    CurveString(vector<Curve<double>*> &);

    //! Constructor
    CurveString(vector<Curve<double>*> &, vector<double> &);

    //! Copy constructor
    CurveString(const CurveString &);

    //! Assignment operator
    CurveString operator=(const CurveString &);

    //! Get number of vertices
    int getNumberOfVertices();

    //! Get number of sides
    int getNumberOfSegments();

    //! Cumulative length of the curves forming the curve string
    double length();

    //! Sampling probabilities of the individual curves
    vector<double> getSampleProbabilities();

    //! Generate random points
    vector<Point<double>> generateRandomPoints(int);

    //! Plots the curve string 
    void draw(string);
};

#endif 

