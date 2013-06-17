#ifndef CURVE_STRING_H
#define CURVE_STRING_H

#include "Header.h"

class Polygon
{
  private:
    //! Vertices of the polygon 
    vector<Point<double>> vertices;

    //! Set of line segments
    vector<Line<double>> sides;

    //! Lengths of the line segments 
    vector<double> lengths;

    //! Select a side
    int getCurveIndex(double, vector<double> &);

  public:
    //! Null constructor
    Polygon();

    //! Constructor
    Polygon(vector<Point<double>> &);

    //! Constructor
    Polygon(vector<Line<double>> &);

    //! Copy constructor
    Polygon(const Polygon &);

    //! Assignment operator
    Polygon operator=(const Polygon &);

    //! Get number of vertices
    int getNumberOfVertices();

    //! Get number of sides
    int getNumberOfSegments();

    //! Cumulative length of the sides forming the polygon 
    double length();

    //! Sampling probabilities of the individual segments
    vector<double> getSampleProbabilities();

    //! Generate random points
    vector<Point<double>> generateRandomPoints(int);

    //! Plots the curve string 
    void draw(string, vector<Point<double>> &);

    //! Write the results to a file
    void save(string, pair<vector<double>,vector<double>> &);
};

#endif 

