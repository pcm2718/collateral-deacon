#include <complex>
#include <vector>



class Mandelbrot
{

public:

  /*
   * Public Methods
   */

  Mandelbrot (long const & max_ittr): MAX_ITTR(max_ittr)
    {
    };



  long
  get_score (std::complex<double> const & cval) const;



  std::vector<std::complex<double>>
  get_trajectory (std::complex<double> const & cval) const;



  /*
   * Public Variables
   */

  long const MAX_ITTR;
};
