#include "Point3D.h"
#include <iostream>
#include <cmath>

using namespace std ;

Point3D :: Point3D()
{
  x = 0 ;
  y = 0 ;
  z = 0 ;
} 

Point3D :: Point3D(double *coord)
{
  x = coord[0] ;
  y = coord[1] ;
  z = coord[2] ;
}

double Point3D :: distance (Point3D &point)
{
  double xdiff = (x - point.x) * (x - point.x) ;
  double ydiff = (y - point.y) * (y - point.y) ;
  double zdiff = (z - point.z) * (z - point.z) ;
  return sqrt(xdiff+ydiff+zdiff);
}

Point3D Point3D :: directionCosines(Point3D &point)
{
  double dcx = point.x - x ;
  double dcy = point.y - y ;
  double dcz = point.z - z ;
  double magnitude = sqrt(dcx*dcx+dcy*dcy+dcz*dcz);
  double *dc = new double[3] ;
  dc[0] = dcx / magnitude ;
  dc[1] = dcy / magnitude ;
  dc[2] = dcz / magnitude ;
  Point3D dcVec (dc) ;
  delete[] dc ;
  return dcVec ;
}

Point3D Point3D :: pointAt (Point3D &dcs, double length)
{
  double point[3];
  point[0] = x + length * dcs.x;
  point[1] = y + length * dcs.y;
  point[2] = z + length * dcs.z;
  return Point3D(point) ;
}

Point3D Point3D :: pointBetween (Point3D &point, double length)
{
  Point3D dcs = directionCosines(point);
  return pointAt(dcs,length) ;
}

void Point3D :: print()
{
  /*cout << "x: " << x << endl ;
  cout << "y: " << y << endl ;
  cout << "z: " << z << endl ;*/
  cout << x << " " << y << " " << z << endl ;
}

