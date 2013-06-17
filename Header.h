#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <cstring>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <cassert>
#include <ctime>
#include <cmath>
#include <liblcb/liblcb.h>
#include <boost/math/constants/constants.hpp>
#include <boost/program_options.hpp>

#define PI boost::math::constants::pi<double>()
#define ZERO std::numeric_limits<double>::epsilon()

#define POINTS_PER_UNIT 10

using namespace std;
using namespace lcb;
using namespace lcb::geometry;
using namespace boost::program_options;

#endif

