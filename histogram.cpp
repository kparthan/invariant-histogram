#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Point3D.cpp"

using namespace std ;

Point3D parseLine(string line)
{
  double point[3];
  char *cstr,*p ;
  cstr = new char [line.size()+1];
  strcpy(cstr,line.c_str());

  p = strtok(cstr," \t\n");
  int i=0,count=0 ;
  while(p!=NULL) {
    point[i++] = atof(p);
    p = strtok(NULL," \t\n");
  }
  delete[] cstr;
  return Point3D (point);
}

vector<Point3D> readFile(string fname)
{ 
  string line ;
  ifstream file (fname.c_str());
  vector<Point3D> list ;
  while (1) {
    getline(file,line);
    if(!file.eof()) {
      Point3D p = parseLine(line) ;
      list.push_back(p);
    }
    else break;
  }
  file.close();
  return list ;
}

double lengthOfCurve (vector<Point3D> &list)
{
  int numPoints = list.size() ;
  double length=0;
  
  for(int i=0; i<numPoints-1; i++) {
    length += list[i].distance(list[i+1]) ;
  }
  return length ;
}

vector<Point3D> generateSamples (double spacing, int numSamples, vector<Point3D> &atoms)
{
  // generate first sample between first two atoms randomly
  double length = atoms[0].distance(atoms[1]);
  double randomNumber = rand()/(double) RAND_MAX;
  double randomLength = randomNumber * length;
  Point3D newSample = atoms[0].pointBetween(atoms[1],randomLength);
  vector<Point3D> samples;
  double temp ;
  
  samples.push_back(newSample);
  int i,count = 1;
  for (i=1; i<numSamples; i++) {
    length = samples[i-1].distance(atoms[count]);
    if (length > spacing) {
      newSample = samples[i-1].pointBetween(atoms[count],spacing);
    } 
    else if (length < spacing) {
      temp = spacing - length ;
      while (temp > 0) {
        if (count == atoms.size()-1) {
          //cout << "Not enough samples ..." << endl ;
          goto end;
        }
        count++; 
        length = atoms[count-1].distance(atoms[count]);
        if (length > temp) {
          newSample = atoms[count-1].pointBetween(atoms[count],temp);
          break ;
        } 
        else if (length < temp) {
          temp -= length ;
        } else {
          newSample = atoms[count-1].pointBetween(atoms[count],temp);
          if (count == atoms.size()-1) {
            //cout << "Not enough samples ..." << endl ;
            goto end ;
          }
          count++ ;
          break ;
        }
      }
    }
    else if (length == spacing) {
      newSample = samples[i-1].pointBetween(atoms[count],spacing);
      if (count == atoms.size()-1) {
        //cout << "Not enough samples ..." << endl ;
        goto end ;
      }
      count++;
    }
    samples.push_back(newSample);
  }

  end:
  if(i < numSamples-1) {
    cout << "# of samples generated: " << i+1 << endl;
    //exit(1);
  } else {
    cout << "# of samples generated: " << i << endl;
  }
  return samples ;
}

int finalizeSamples (vector<string> &pdb, vector<vector<Point3D> > &proteinSamples)
{
  int i,numProteins = pdb.size();

  // determine minimum number of samples
  int minSamples = proteinSamples[0].size();
  for (i=1; i<numProteins; i++) {
    if (proteinSamples[i].size() < minSamples) {
      minSamples = proteinSamples[i].size() ;
    }
  }
  
  // truncate the extra samples if required
  for (i=0; i<numProteins; i++) {
    if (minSamples != proteinSamples[i].size()) {
      int extra = proteinSamples[i].size() - minSamples;
      for (int j=0; j<extra; j++) {
        proteinSamples[i].pop_back() ;
      }
    }
  }

  return minSamples;
}

vector<double> localHistogramFunction(vector<Point3D> &samples, double r)
{
  vector<double> histogram;
  int numSamples = samples.size();
  int count;
  for (int i=0; i<numSamples; i++) {
    count = 0;
    for (int j=0; j<numSamples; j++) {
      if (samples[i].distance(samples[j]) <= r) {
        count++;
      }
    }
    histogram.push_back((double)count/numSamples);
  }
  return histogram;
}

double globalHistogramFunction(vector<double> &localHistogram, double spacing, double length)
{
  double histogram = 0;
  for (int i=0; i<localHistogram.size(); i++) {
    histogram += localHistogram[i];
  }
  return histogram * spacing / length;
}

// computes similarity for a given r
void computeSimilarity(vector<string> &pdb, vector<vector<Point3D> > &proteinSamples, 
                       vector<double> &equalSpacing, vector<double> &length, double r)
{
  int numProteins = pdb.size();
  vector<vector<double> > comparison;
  vector<double> similarity(numProteins,0);
  int i,j;
  vector<double> localHistogram;
  vector<double> globalHistogram;

  for (i=0; i<numProteins; i++){
    localHistogram = localHistogramFunction(proteinSamples[i],r);
    globalHistogram.push_back(globalHistogramFunction(localHistogram,equalSpacing[i],length[i]));
  }

  for (i=0; i<numProteins; i++) {
    for (j=0; j<numProteins; j++) {
      if (j < i) {
        similarity[j] = comparison[j][i] ;
      }
      else if (j > i) {
        similarity[j] = fabs(globalHistogram[i]/equalSpacing[i] - globalHistogram[j]/equalSpacing[j]) * 100  ;
      } else {
        similarity[j] = 0;
      }
    }
    comparison.push_back(similarity);
  }

  // printing the comparison matrix
  ofstream file ("similarity.txt");
  file << "\t\t\t" ;
  for(i=0; i<numProteins; i++) {
    file << setw(10) << pdb[i] ;
  }
  file << endl << "-----------------------------------------------";
  for (i=0; i<numProteins; i++) {
    file << endl << pdb[i] << "\t" ;
    for (j=0; j<numProteins; j++) {
      file << setw(10) << comparison[i][j] ;
    }
  }
  file.close() ;
}

void prepareGnuplotScript(vector<string> &pdb, double rmin, double rmax, int numSamples)
{
  ofstream script ("plotScript.p");
  const char *color[] = {"red","blue","green","brown"};
  script << "# Gnuplot script script for plotting global histogram values" << endl ;
  script << "# for different values of r" << endl << endl ;
  script << "set terminal png small" << endl ;
  script << "set autoscale # scale axes automatically" << endl ;
  script << "set xtic auto # set xtics automatically" << endl ;
  script << "set ytic auto # set ytics automatically" << endl ;
  script << "set title \"COMPARISON OF GLOBAL HISTOGRAM FUNCTIONS\\n[Number of samples = " << numSamples << "]\"" << endl  ;
  script << "set xlabel \"r\"" << endl ; 
  script << "set ylabel \"global histogram value\"" << endl ;
  script << "set xr [" << rmin << ":" << rmax << "]" << endl ;
  script << "set yr [0:1.2]" << endl ;
  script << "set output \"comparison.png\"" << endl ;
  script << "set multiplot" << endl ;
  script << "plot " ;
  for (int i=1; i<=pdb.size(); i++) {
    script << "\"results.txt\" using 1:" << i+1 << " title '" << pdb[i-1] << "' \\" << endl ;
    script << "with points lc rgb \"" << color[i-1] << "\"" ;
    if (i != pdb.size()) {
      script << ", \\" << endl ;
    }
  }
  script.close();

  system("gnuplot -persist plotScript.p") ;
}

void plot(vector<string> &pdb, vector<vector<Point3D> > &proteinSamples, 
          vector<double> &equalSpacing, vector<double> &length)
{
  vector<double> localHistogram;
  double globalHistogram;
  
  double rmin = 0, rmax = 50;
  ofstream file ("results.txt");
  for (double r=rmin; r<rmax; r++) {
    file << r << " " ;
    for (int i=0; i<pdb.size(); i++) {
      localHistogram = localHistogramFunction(proteinSamples[i],r);
      globalHistogram = globalHistogramFunction(localHistogram,equalSpacing[i],length[i]);
      file << globalHistogram << " ";
    }
    file << endl;
  }
  file.close();

  prepareGnuplotScript(pdb,rmin,rmax,proteinSamples[0].size());
}

int main(int argc, char **argv)
{
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <number of samples> <r>" << endl ;
    exit(1) ;
  }
  string fname;
  string pdbID[] = {"1hhoa","1idr","1mbd","2snv"} ;
  vector<string> pdb(pdbID,pdbID+4);
  int i; 
  vector<Point3D> atoms,samples;
  vector<vector<Point3D> > proteins,proteinSamples ;
  vector<double> length,equalSpacing,localHistogram;
  double globalHistogram;

  int numSamples = atoi(argv[1]) ;
  double r = atof(argv[2]);

  for (i=0; i<pdb.size(); i++) {
    fname = "parsed/" + pdb[i] ;
    atoms = readFile(fname.c_str());
    proteins.push_back(atoms);
    length.push_back(lengthOfCurve(proteins[i]));
    cout << "Length of curve: " << length[i] << endl ;
    equalSpacing.push_back(length[i] / (double)numSamples);
  }

  for (i=0; i<pdb.size(); i++) {
    samples = generateSamples(equalSpacing[i],numSamples,proteins[i]);
    proteinSamples.push_back(samples);

    /*localHistogram = localHistogramFunction(proteinSamples[i],r);
    globalHistogram = globalHistogramFunction(localHistogram,equalSpacing,length);
    cout << globalHistogram << endl ;*/
  }
  numSamples = finalizeSamples(pdb,proteinSamples);

  // sanity check
  cout << "number: " << numSamples << endl ;
  /*for(i=0; i<pdb.size(); i++) {
    cout << proteinSamples[i].size() << endl ;
  }*/

  computeSimilarity(pdb,proteinSamples,equalSpacing,length,r);

  plot(pdb,proteinSamples,equalSpacing,length) ;

  return 0;
}

