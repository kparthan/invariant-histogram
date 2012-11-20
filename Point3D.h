#ifndef _POINT3D_H
#define _POINT3D_H

class Point3D
{
  private:
    double x,y,z ;
  public:
    Point3D() ;
    Point3D(double *) ;
    double distance(Point3D &);
    Point3D directionCosines(Point3D &);
    Point3D pointAt(Point3D &, double) ; // given dcs
    Point3D pointBetween(Point3D &, double);
    void print();
} ;

#endif

