#ifndef CURVE_STRING_H
#define CURVE_STRING_H

class CurveString
{
  private:
    //! Vertices of the segments of the curves 
    vector<Point<double>> vertices;

    //! Set of curves
    vector<Curve<double>> curves;

    //! Select a curve
    int getCurveIndex(double, vector<double> &);

  public:
    //! Null constructor
    CurveString();

    //! Constructor
    CurveString(vector<Point<double>> &);

    //! Constructor
    CurveString(vector<Curve<double>> &);

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

    //!
    double computeDistanceHistogram(int, double);

    //! Plots the polygon
    void draw();
};

#endif 

