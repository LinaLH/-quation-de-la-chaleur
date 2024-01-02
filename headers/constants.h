#ifndef CONSTANTS_H // to avoid multiple inclusions
#define CONSTANTS_H

#include <cmath>

namespace cst
{
    // initial temperature
    const double u_0 = 286.15; // 13 Celsius degrees = 286,15 Kelvin degrees (13°C + 273,15 = 286 K)
    // bar length
    const double L = 1.0; // 1m
    // time of observation
    const double tmax = 16.0; // 16s
    // temperature of the heat source
    const double f = 353.15; // f = 80°C = 353,15 K

    // time discretisation
    const double N_time = 1001;
    // space discretisation
    const double N_space = 1001;

    // time intervals
    const double delta_t = tmax / N_time; // (tmax - tmin) / N
    // space intervals
    const double delta_x = L / N_space; // (xmax - xmin) / N

    // SDL
    // window width
    const int WINDOW_WIDTH = 1240;
    // window height
    const int WINDOW_HEIGHT = 800;
    // number of points
    const int t_val = 100;
}

#endif