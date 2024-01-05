#ifndef CONSTANTS_HPP // to avoid multiple inclusions
#define CONSTANTS_HPP

#include <cmath>

namespace cst
{
    // initial conditions
    const double L = 1.0;        // 1m
    const double tmax = 16.0;    // 16s
    const double u_0 = 286.15;   // 13°C + 273,15 = 286,15 K
    const double f = 353.15;     // f = 80°C + 273,15 = 353,15 K
    const double N_time = 1001;  // time discretisation
    const double N_space = 1001; // space discretisation

    // time and space intervals
    const double delta_t = tmax / N_time; // (tmax - tmin) / N
    const double delta_x = L / N_space;   // (xmax - xmin) / N

    // SDL constants
    const int window_width = 1240;
    const int window_height = 800;
    const int t_val = 100; // number of points
}

#endif