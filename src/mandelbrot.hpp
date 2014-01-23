#include <complex>
#include <vector>



class Mandelbrot
{

public:

  /*
   * Public Methods
   */

  Mandelbrot::Mandelbrot (long max_ittr): MAX_ITTR(max_ittr)
    {
    };



  long
  Mandelbrot::get_score (const std::complex<double> cval);



  std::vector<std::complex<double>>
  Mandelbrot::get_trajectory (const std::complex<double> cval);



  /*
   * Public Variables
   */

  const long MAX_ITTR;
};
