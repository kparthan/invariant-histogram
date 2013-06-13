#include "CurveString.h"

/*!
 *  \brief This module is a null constructor.
 */
CurveString::CurveString()
{}

/*!
 *  \brief This is a constructor function.
 *  \param vertices a reference to a vector<Point<double>>
 */
CurveString::CurveString(vector<Point<double>> &vertices) : vertices(vertices)
{
  if (vertices.size() == 0) {
    cout << "No vertices to construct the curve string ...";
    exit(1);
  }
  // Default behaviour: constructs a curve string when a set of vertices are given
  for (int i=0; i<vertices.size()-1; i++) {
    Line<double> line(vertices[i],vertices[i+1]);
    curves.push_back(line);
  }
}

/*!
 *  \brief This is a constructor function.
 *  \param curves a reference to a vector<Line<Point<double>>>
 */
CurveString::CurveString(vector<Curve<double>> &curves) : curves(curves)
{
  if (curves.size() == 0) {
    cout << "No curves to construct the curve string ...";
    exit(1);
  }
  vertices.push_back(curves[0].startPoint());
  for (int i=0; i<curves.size(); i++) {
    vertices.push_back(curves[i].endPoint());
  }
}

/*!
 *  \brief This module is used to create a copy of a CurveString object
 *  \param source a reference to a CurveString
 */
CurveString::CurveString(const CurveString &source) : 
                         vertices(source.vertices), curves(source.curves) 
{}

/*!
 *  \brief This module assigns a source curve string to a target curve string.
 *  \param source a reference to a CurveString
 *  \return a CurveString
 */
CurveString CurveString::operator=(const CurveString &source)
{
  if (this != &source) {
    vertices = source.vertices;
    curves = source.curves;
  }
  return *this;
}

/*!
 *  \brief This method is used to return the number of vertices of the curve string
 *  \return the number of vertices
 */
int CurveString::getNumberOfVertices()
{
  return vertices.size();
}

/*!
 *  \brief This method is used to return the number of curves of the curve string
 *  \return the number of curves
 */
int CurveString::getNumberOfSegments()
{
  return curves.size();
}

/*!
 *  \brief This method computes the length of the curve string
 *  \return the length of all curves
 */
double CurveString::length()
{
  double sum = 0;
  for (int i=0; i<curves.size(); i++) {
    sum += curves[i].length(); 
  }
  return sum;
}

/*!
 *  \brief This method computes the sampling probabilities of each curve
 *  comprising the curve string
 *  \return the list of sampling probabilities
 */
vector<double> CurveString::getSampleProbabilities()
{
  vector<double> lengths;
  double sum = 0;
  for (int i=0; i<curves.size(); i++) {
    double length = curves[i].length();
    sum += length;
    lengths.push_back(length);
  }
  vector<double> sample_probability(curves.size(),0);
  for (int i=0; i<curves.size(); i++) {
    sample_probability[i] = lengths[i] / sum;
  }
  return sample_probability;
}

/*!
 *  \brief This function returns the curve index generated randomly
 *  \param random a double
 *  \param sample_probability a reference to a vector<double>
 *  \return the appropriate curve index
 */
int CurveString::getCurveIndex(double random, vector<double> &sample_probability)
{
  double previous = 0;
  for (int i=0; i<sample_probability.size(); i++) {
    if (random <= sample_probability[i] + previous) {
      return i;
    }
    previous += sample_probability[i];
  }
}

/*!
 *  \brief This method is used to sample points on the curve string.
 *  \param num_samples an integer
 *  \return a list of random points
 */
vector<Point<double>> CurveString::generateRandomPoints(int num_points)
{
  srand(time(NULL));
  vector<Point<double>> samples;
  vector<double> sample_probability = getSampleProbabilities();
  for (int i=0; i<num_points; i++) {
    // randomly choose a side of the curve string
    double random = rand() / (double) RAND_MAX;
    int curve_index = getCurveIndex(random,sample_probability);

    // randomly choose the parameter value \in [0,1]
    double t = rand() / (double) RAND_MAX;
    Point<double> point_on_curve = curves[curve_index].getPoint(t);

    samples.push_back(point_on_curve);
  }
  return samples;
}

/*!
 *  \brief This function computes the distance histogram function for 
 *  the curve string.
 *  \param num_samples an integer
 *  \param r a double
 *  \return the histogram function value
 */
double CurveString::computeDistanceHistogram(int num_samples, double r)
{
  vector<Point<double>> samples = generateRandomPoints(num_samples);
  //DistanceHistogram histogram(samples);
  //histogram.computeGlobalHistogram(r);
}

/*!
 *  \brief This method plots the curve string.
 */
void CurveString::draw()
{

}

