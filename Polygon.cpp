#include "Polygon.h"

/*!
 *  \brief This module is a null constructor.
 */
Polygon::Polygon()
{}

/*!
 *  \brief This is a constructor function.
 *  \param vertices a reference to a vector<Point<double>>
 */
Polygon::Polygon(vector<Point<double>> &vertices) : vertices(vertices)
{
  if (vertices.size() == 0) {
    cout << "No vertices to construct the polygon ...";
    exit(1);
  }
  for (int i=0; i<vertices.size()-1; i++) {
    Line<double> line(vertices[i],vertices[i+1]);
    sides.push_back(line);
    lengths.push_back(line.length());
  }
}

/*!
 *  \brief This is a constructor function.
 *  \param sides a reference to a vector<Line<Point<double>>>
 */
Polygon::Polygon(vector<Line<double>> &sides) : sides(sides)
{
  if (sides.size() == 0) {
    cout << "No sides to construct the polygon ...";
    exit(1);
  }
  vertices.push_back(sides[0].startPoint());
  for (int i=0; i<sides.size(); i++) {
    vertices.push_back(sides[i].endPoint());
    lengths.push_back(sides[i].length());
  }
}

/*!
 *  \brief This module is used to create a copy of a Polygon object
 *  \param source a reference to a Polygon
 */
Polygon::Polygon(const Polygon &source) : vertices(source.vertices),
         samples(source.samples), sides(source.sides), lengths(source.lengths)
{}

/*!
 *  \brief This module assigns a source curve string to a target curve string.
 *  \param source a reference to a Polygon
 *  \return a Polygon
 */
Polygon Polygon::operator=(const Polygon &source)
{
  if (this != &source) {
    vertices = source.vertices;
    sides = source.sides;
    lengths = source.lengths;
    samples = source.samples;
  }
  return *this;
}

/*!
 *  \brief This method is used to return the number of vertices of the curve string
 *  \return the number of vertices
 */
int Polygon::getNumberOfVertices()
{
  return vertices.size();
}

/*!
 *  \brief This method is used to return the number of sides of the curve string
 *  \return the number of sides
 */
int Polygon::getNumberOfSegments()
{
  return sides.size();
}

/*!
 *  \brief This method computes the length of the curve string
 *  \return the length of all sides
 */
double Polygon::length()
{
  double total_length = 0;
  for (int i=0; i<lengths.size(); i++) {
    total_length += lengths[i]; 
  }
  return total_length;
}

/*!
 *  \brief This method computes the sampling probabilities of each curve.
 *  \return the list of sampling probabilities
 */
vector<double> Polygon::getSampleProbabilities()
{
  double total_length = length();
  vector<double> sample_probability(sides.size(),0);
  for (int i=0; i<sides.size(); i++) {
    sample_probability[i] = lengths[i] / total_length;
  }
  return sample_probability;
}

/*!
 *  \brief This function returns the curve index generated randomly
 *  \param random a double
 *  \param sample_probability a reference to a vector<double>
 *  \return the appropriate curve index
 */
int Polygon::getCurveIndex(double random, vector<double> &sample_probability)
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
vector<Point<double>> Polygon::generateRandomPoints(int num_points)
{
  srand(time(NULL));
  //vector<Point<double>> samples;
  vector<double> sample_probability = getSampleProbabilities();
  for (int i=0; i<num_points; i++) {
    // randomly choose a side of the curve string
    double random = rand() / (double) RAND_MAX;
    int curve_index = getCurveIndex(random,sample_probability);

    // randomly choose the parameter value \in [0,1]
    double t = rand() / (double) RAND_MAX;
    Point<double> point_on_curve = sides[curve_index].getPoint(t);

    samples.push_back(point_on_curve);
  }
  return samples;
}

/*!
 *  \brief This method plots the curve string.
 *  \param file_name a string
 */
void Polygon::draw(string file_name, vector<Point<double>> &samples)
{
  string data = "test/" + file_name + ".actual";
  ofstream data_file(data.c_str());
  double dt = 0.01;
  for (int i=0; i<sides.size(); i++) {
    for (double t=0; t<=1; t+=dt) {
      Point<double> p = sides[i].getPoint(t);
      data_file << p.x() << " " << p.y() << endl;
    }
  }
  data_file.close();
  string sample_data = "test/" + file_name + ".samples";
  ofstream samples_file(sample_data.c_str());
  for (int i=0; i<samples.size(); i++) {
    samples_file << samples[i].x() << " " << samples[i].y() << endl;
  }
  samples_file.close();
}

/*!
 *
 */
void Polygon::write(string file, pair<vector<double>,vector<double>> &results)
{
  string file_name = "results/" + file + ".results";
  ofstream fp (file_name.c_str());
  vector<double> r = results.first;
  vector<double> f = results.second;
  assert(r.size() == f.size());
  for (int i=0; i<r.size(); i++) {
    fp << r[i] << " " << f[i] << endl;
  }
  fp.close();
}


