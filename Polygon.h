#ifndef POLYGON_H
#define POLYGON_H

#include "Header.h"
#include "Curve.h"

class Polygon : public Curve
{
  private:
    //! Vertices of the polygon
    vector<Point<double>> vertices;

    //! Sides of the polygon
    vector<Line<Point<double>>> sides;

  public:
    //! Null constructor
    Polygon();

    //! Constructor
    Polygon(vector<Point<double>> &);

    //! Constructor
    Polygon(vector<Line<Point<double>>> &);

    //! Copy constructor
    Polygon(const Polygon &);

    //! Assignment operator
    Polygon operator=(const Polygon &);

    //! Get number of vertices
    int getNumberOfVertices();

    //! Get number of sides
    int getNumberOfSides();

    //! Length of the polygon
    double length();

    //! Generate random points
    vector<Point<double>> generateRandomPoints(int);

    //!
    double computeDistanceHistogram(int, double);

    //! Plots the polygon
    void draw();
};

#endif

