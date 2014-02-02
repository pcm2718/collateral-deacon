#include <complex>
#include <vector>
#include <random>

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
    MAX_ITTR (max_ittr),
    rng (std::mt19937 (std::random_device () ())),
    real_dist (std::uniform_real_distribution<double> (std::real (C_DOMAIN.first), std::real (C_DOMAIN.second))),
    imag_dist (std::uniform_real_distribution<double> (std::imag (C_DOMAIN.first), std::imag (C_DOMAIN.second)))
  {
  }



  std::vector<std::complex<double>>
  get_points (long const c_count);



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
  generate_trajectory (std::complex<double> const & c_val) const;



  /*
   * Private Variables
   */

  std::mt19937 rng;

  std::uniform_real_distribution<double> real_dist;

  std::uniform_real_distribution<double> imag_dist;
};
