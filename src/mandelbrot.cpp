#include "mandelbrot.hpp"



long
Mandelbrot::get_score (std::complex<double> const & cval) const
  {
    auto zval = std::complex<double> (0, 0);

    long n = 1;
    for ( ; n <= MAX_ITTR && std::abs (zval) < 2 ; ++n )
      {
	zval = std::pow (zval, 2) + cval;
      }
    
    return n;
  };



/*
 * This function needs to be checked for correctness.
 */
std::vector<std::complex<double>>
Mandelbrot::get_trajectory (std::complex<double> const & cval) const
  {
    auto trajectory = std::vector<std::complex<double>> ();
    auto zval = std::complex<double> (0, 0);
  
    for (long n = 0 ; n < MAX_ITTR ; ++n )
      {
	/*
	 * This condition may be buggy.
	 */
        if (std::abs (zval) > 2)
	  break;
      
        trajectory.push_back(zval);
        zval = std::pow (zval, 2) + cval;
      }
    
    if (std::abs (zval) < 2)
      return std::vector<std::complex<double>> ();
    else
      return trajectory;
  };
