#include "mandelbrot.hpp"



long
Mandelbrot::get_score (const std::complex<double> cval)
  {
    auto zval = std::complex<double> (0, 0);

    long n = 1;
    for ( ; n <= MAX_ITTR && std::abs (zval) < 2 ; ++n)
      {
	zval = std::pow (zval, 2) + cval;
      }
    
    return n;
  };



std::vector<std::complex<double>>
Mandelbrot::get_trajectory (const std::complex<double> cval)
  {
    auto trajectory = std::vector<std::complex<double>> ();
    auto zval = std::complex<double> (0, 0);
  
    for (long n = 0 ; n < MAX_ITTR &&  ; ++n)
      {
        if (std::abs (zval) < 2)
	  return std::vector<std::complex<double>> ();
      
        trajectory.push_back(zval);
        zval = std::pow (zval, 2) + cval;
      }
  
    return trajectory;
  };
