#include <complex>
#include <vector>



class Mandelbrot
{

public:

  /*
   * Public Methods
   */

  Mandelbrot (long max_ittr): MAX_ITTR(max_ittr)
    {
    };



  long
  get_score (const std::complex<double> cval);



  std::vector<std::complex<double>>
  get_trajectory (const std::complex<double> cval);



  /*
   * Public Variables
   */

  const long MAX_ITTR;
};
