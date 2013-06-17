#include "Support.h"

/*!
 *  \brief This function checks to see if valid arguments are given to the 
 *  command line output.
 *  \param argc an integer
 *  \param argv an array of strings
 *  \return the number of samples to be generated on the curves 
 */
int parseCommandLineInput(int argc, char **argv)
{
  int num_points;

  options_description desc("Allowed options");
  desc.add_options()
       ("help","produce help message")
       ("n",value<int>(&num_points),"# of samples to be generated")
  ;
  variables_map vm;
  store(parse_command_line(argc,argv,desc),vm);
  notify(vm);

  if (vm.count("help")) {
    Usage(argv[0],desc);
  }
  
  if (!vm.count("n")) {
    num_points = 0;
  }

  return num_points;
}

/*!
 *  \brief This module prints the acceptable input format to the program
 *  \param exe a reference to a const char
 *  \param desc a reference to a options_description object
 */
void Usage (const char *exe, options_description &desc)
{
  cout << "Usage: " << exe << " [options]" << endl;
  cout << desc << endl;
  exit(1);
}

/*!
 *  \brief This method is used to compare the structures by plotting the
 *  respective histogram function values.
 */
void compareResults()
{
  ofstream script("script.plot");
  script << "set terminal post eps" << endl;
  script << "set title \"Histogram Comparison\"" << endl;
  script << "set xlabel \"r\"" << endl;
  script << "set ylabel \"global histogram function\"" << endl;
  script << "set yr [0:1.5]" << endl;
  script << "set output \"output/histogram_comparison.eps\"" << endl;
  script << "set multiplot" << endl;
  script << "plot \"output/square.results\" using 1:2 title "
         << "'square' with points lc rgb \"red\", \\" << endl;
  script << "\"output/rhombus.results\" using 1:2 title "
         << "'rhombus' with points lc rgb \"blue\", \\" << endl;
  script << "\"output/rectangle.results\" using 1:2 title "
         << "'rectangle' with points lc rgb \"green\"" << endl;
  script.close();
  system("gnuplot -persist script.plot");
}

