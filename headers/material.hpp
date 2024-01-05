#ifndef MATERIAL_HPP // to avoid multiple inclusions
#define MATERIAL_HPP

namespace materials
{
    namespace cuivre
    {
        const double lambda = 389.0; // W/(m.K)
        const double rho = 8940.0;   // kg/m3
        const double c_mat = 380.0;  // J/(kg.K)
    }
    namespace fer
    {
        const double lambda = 80.2;
        const double rho = 7874.0;
        const double c_mat = 440.0;
    }
    namespace verre
    {
        const double lambda = 1.2;
        const double rho = 2530.0;
        const double c_mat = 840.0;
    }
    namespace polystyrene
    {
        const double lambda = 0.1;
        const double rho = 1040.0;
        const double c_mat = 1200.0;
    }
}

#endif
