#include <complex>
#include <vector>
#include <chrono>
#include <random>



// This may be incorrect usage.
using CDomain = std::pair<std::complex<double>, std::complex<double>>;



class Pointgen
{
public:

  /*
   * Public Methods
   */

  Pointgen (
            CDomain const & c_domain,
            long const max_ittr ) :
    C_DOMAIN (c_domain),
    MAX_ITTR (max_ittr)
  {
  }



  std::vector<std::complex<double>>
  get_points (long const point_count) const;



  /*
   * Public Variables
   */

  std::pair<std::complex<double>, std::complex<double>> const C_DOMAIN;

  long const MAX_ITTR;



private:

  /*
   * Private Methods
   */

  std::vector<std::complex<double>>
  generate_trajectory (std::complex<double> const & cval) const;
};
